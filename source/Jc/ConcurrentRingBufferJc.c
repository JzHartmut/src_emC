/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 * list of changes:
 * 2008-05-00: JcHartmut creation
 *
 ****************************************************************************/
/*
 */

struct MemAreaC_t;
#include <Jc/ConcurrentRingBufferJc.h>
#include <os_AtomicAccess.h>
#include <emC/Exception.h>
#include <emC/simpleC.h>
#include <string.h>


#define ITEMREF void volatile*
#define NULL_ITEMREF ((void volatile*)null)


static int stop()
{ return 0;
}

/**
 * Creates a <tt>ConcurrentRingBuffer</tt> that is initially empty.
 */
void ctorc_ConcurrentRingBufferJc(ConcurrentRingBufferJc* ythis, MemC ringarea, MemC writeAreas) 
{ init0_MemC(build_MemC(ythis, sizeof(*ythis)));
  init0_MemC(ringarea);
  init0_MemC(writeAreas);
  //*(struct MemAreaC_t**)&ythis->begin = start_MemC(ringarea);
  //*(struct MemAreaC_t**)&ythis->end = addOffset_MemAreaC(end_MemC(ringarea), -1);
  ythis->begin = (struct MemAreaC_t*)start_MemC(ringarea);
  ythis->end = addOffset_MemAreaC(end_MemC(ringarea), -1);
  ythis->read = ythis->begin;
  ythis->written = ythis->begin;
  ythis->next = ythis->begin;
  ythis->writeAreas = (WriteArea_ConcurrentRingBufferJc*)start_MemC(writeAreas);
  ythis->lengthWriteAreas = size_MemC(writeAreas) / sizeof(WriteArea_ConcurrentRingBufferJc);

}

ConcurrentRingBufferJc* ctor_ConcurrentRingBufferJc(MemC rawMem, MemC ringArea, MemC writeArea) 
{ ConcurrentRingBufferJc* ythis = PTR_MemC(rawMem, ConcurrentRingBufferJc);
  STACKTRC_ENTRY("ctor_ConcurrentRingBufferJc");
  if(size_MemC(rawMem) < sizeof(ConcurrentRingBufferJc)) 
  { THROW_s0(IllegalArgumentException,"size to less", size_MemC(rawMem)); }
  ctorc_ConcurrentRingBufferJc(ythis, ringArea, writeArea);
  STACKTRC_LEAVE; return ythis;
}

bool add_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis, void const* data, int sizeData) 
{
    return offer_ConcurrentRingBufferJcF(ythis, data, sizeData);
}

/**
 * Inserts the specified data at write position.
 * Normal case:     
 *   ...next++++nextNew....
 * it interrupts another thread: 
 *   ...written######next+++++++nextNew....
 * The area #### will be filled from the lower prior interrupted thread after the own operation.
 * 
 * @return true if the node is added, false if not.
 */
bool offer_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis, void const* data, int sizeData) 
{ bool bSufficing = true;
  //bool isLockedFromMe;
  struct MemAreaC_t* myBegin;
  struct MemAreaC_t* myEnd;
  int idxWriteArea;
  int sizeToEnd = 0;
  #ifdef TEST_testIntteruptingThread
    int testState = 0;
  #endif
  STACKTRC_ENTRY("offer_ConcurrentRingBufferJcF");
  if(sizeData < 0){ sizeData = strlen((const char*)data); }
  //isLockedFromMe = compareAndSet_AtomicInteger(&ythis->lock, 0, 1);
  { //First phase: Test and reserve memory.
    int nrofRepeatSetNext = -1;
    bool bSuccess;
    do
    { myBegin = ythis->next;
      myEnd = addOffset_MemAreaC(myBegin, sizeData);
    
      //Test if the expected myBegin is the same as written at this time.
      //If it is so and ythis->next is equal myBegin still, because CompareAndSet was successfull,
      //no other thread can change ythis->written, because this condition can only true here. 
      idxWriteArea = -1; //default no Write Area necessary.
      if(myBegin != ythis->written)
      { //another thread is interrupted, which is writing in the same RingBuffer.
        //Than an entry to store the written area is necessary. Search it first,
        //because if there is no free entry, the offer fails.
        int idxWriteAreaTest = 0;
        while(idxWriteArea == -1 && idxWriteAreaTest < ythis->lengthWriteAreas)
        { WriteArea_ConcurrentRingBufferJc* writeArea = &ythis->writeAreas[idxWriteAreaTest];
          if(writeArea->begin == null)
          { //found null from begin, start on next search at next index!
            if(compareAndSet_AtomicReference(CAST_AtomicReference(writeArea->begin), null, (void*)-1))
            { //it is occupied:
              idxWriteArea = idxWriteAreaTest;
            }
          }
          else
          { //another write area entry:
            idxWriteAreaTest +=1; 
          }
        }
        if(idxWriteArea <0)
        { //no space for writearea, offer fails!
          bSufficing = false;
        }
      }
      if(bSufficing)
      { //before change next, test wether it is enaugh space.
        //only if it has space, next should be changed.
        struct MemAreaC_t* read = ythis->read;  //get read one time, hold local (it is volatile)
        if(read > myBegin)
        { //++++nb-----e...........r++++++
          bSufficing = (read >= myEnd);
        }
        else
        { //.....r++++++++nb-----e........
          bSufficing = ythis->end > myEnd;  //ok if the new content is fit to the end
          if(!bSufficing)
          { //--e............r++++++++nb---
            sizeToEnd = offset_MemAreaC(myBegin, ythis->end);
            myEnd = addOffset_MemAreaC(ythis->begin, (sizeData - sizeToEnd));
            bSufficing = read >= myEnd;
          }
        }
      }
      #ifdef TEST_testIntteruptingThread
        testIntteruptingThread(++testState);
      #endif
      if(!bSufficing)
      { //the area is to less for the data, no data will be stored.
        bSuccess = true; //but it is successfull, break the try-loop.
      }
      else
      { //try to set the new next position.
        //until this state no change in the buffer is done.
        //here the next pointer is trying to set.
        //only if it is successed, data are copied. Otherwise the operation to find an area is repeated. 
        bSuccess = compareAndSet_AtomicReference(CAST_AtomicReference(ythis->next), myBegin, myEnd);
      }
      nrofRepeatSetNext+=1;
    }while(!bSuccess && nrofRepeatSetNext < 1000);
    if(nrofRepeatSetNext >0)
    { if(nrofRepeatSetNext >=1000) THROW_s0(RuntimeException, "to many repeats trying set next", 1000);
      ythis->dbgcntRepeatSetNext += nrofRepeatSetNext;
      if(ythis->dbgmaxRepeatSetNext < nrofRepeatSetNext){ ythis->dbgmaxRepeatSetNext = nrofRepeatSetNext; }
    }
  }


  //Second phase: Write data into the known are from myBegin to myEnd.
  if(bSufficing)
  { //the next pointer is set to a new next position,
    //it means, another thread can write data after it. It is finishid.
    //but the written pointer is not changed yet, it means, a read don't read ower data yet.
    //The data will be copied now:
    if(sizeToEnd >0)
    { memcpy(myBegin, data, sizeToEnd);
      if(sizeData > sizeToEnd)
      { memcpy(ythis->begin, addOffset_MemAreaC(data, sizeToEnd), sizeData - sizeToEnd);
      }
    }
    else
    { memcpy(myBegin, data, sizeData);
    }
    #ifdef TEST_testIntteruptingThread
      testIntteruptingThread(21);
    #endif
  }
  //Now the data are written and the written pointer can be set.
  /*
  if(!isLockedFromMe)
  { //This call has interrupted a current access,
    //try to set lock again, it is possible if another thread was interrupted,
    //but they is finished now, and no lock is pending.
    //Than this thread gets the monitor and have to be adjust written.
    isLockedFromMe = compareAndSet_AtomicInteger(&ythis->lock, 0, 1);
    if(isLockedFromMe)
    { //in fact the lock was free.
      ythis->dbgcntGetMonitorAfterSetNext ++;
    }  
  }
  */
  #ifdef TEST_testIntteruptingThread
    testState = 0;
  #endif
  
  if(bSufficing)
  { //Third phase: try to set written pointer.
    if(idxWriteArea >=0)
    { //Another thread is interrupted while writing in this RingBuffer. 
      //Store the written area in writeAreas.
      //But first search wether the area is connectable to another area, increase it than.
      //This case is important, because if it is written in the RingBuffer more and more from the same thread,
      //or another thread but sequenced, the thread hadN't interrupted each other,
      //only one entry is necessary. So the number of entries can calculate with the nr of threads using this RingBuffer.
      WriteArea_ConcurrentRingBufferJc* writeArea;
      int idxWriteAreaTest = 0;
      bool bDone = false;
      int lengthWriteAreas = ythis->lengthWriteAreas;
      while(!bDone && idxWriteAreaTest < lengthWriteAreas)
      { writeArea = &ythis->writeAreas[idxWriteAreaTest];
        if(writeArea->end == myBegin)
        { //found a increaseable area.
          //but it is possible that this area is processed just now.
          struct MemAreaC_t* beginTestArea = writeArea->begin;
          bool bLocked = compareAndSet_AtomicReference(CAST_AtomicReference(writeArea->begin), beginTestArea, (void*)-1);
          if(bLocked)
          { //if it contains -1 as pointer, it won't processed.
            writeArea->end = myEnd;
            writeArea->begin = beginTestArea;  //write the correct pointer again.
            bDone = true;
            ythis->writeAreas[idxWriteArea].begin = null;  //free the designated area.
          }
          else
          { idxWriteAreaTest = lengthWriteAreas;  //abort search, another won't found.
          }
        }
        else
        { //another write area entry:
          idxWriteAreaTest +=1; 
        }
      }
      if(!bDone)
      { //set the designated area.
        writeArea = &ythis->writeAreas[idxWriteArea];
        writeArea->end = myEnd;     //set it first because setting begin, the entry will be acute
        writeArea->begin = myBegin; //it was reserved before, setting -1 into it.
      }
    }
    else
    { //ythis->written == myBegin at this time.
      //No other thread had change ythis->written, because this condition is true only here.
      //Set myWritten.
      bool bSetWritten = compareAndSet_AtomicReference(CAST_AtomicReference(ythis->written), myBegin, myEnd);   
      ASSERTJc_TEST(bSetWritten);
    }
    { //some other threads may have stored data, and they haven't set written,
      //but they stored its data area into writeAreas.
      //search and process that areas.
      int idxWriteAreaTest = 0;
      bool bOnlyFoundNull = true;
      bool bSetWritten = true;
      void* written = ythis->written;
      while(bSetWritten && idxWriteAreaTest < ythis->lengthWriteAreas)
      { WriteArea_ConcurrentRingBufferJc* writeArea = &ythis->writeAreas[idxWriteAreaTest];
        if(writeArea->begin == written)
        { //found the entry which is the connection to the current myEnd,
          //increase the written area, set myEnd with the end of found entry.
          void* writtenNew = writeArea->end;
          //myEnd is the highest value found in write area of all other threads,
          //which can't set written itself. Set it now.
          //from this time a interrupting thread can set myWritten itself.
          bSetWritten = compareAndSet_AtomicReference(CAST_AtomicReference(ythis->written), written, writtenNew);   
          written = writtenNew;
          writeArea->end = null;
          writeArea->begin = null;  //free it. Now it can be used in another thread.
          //search from begin of non-null area entries because it is possible that another thread has enter a write area meanwhile.
          //But if there are no more entries found, thread
          idxWriteAreaTest = 0;     
        }
        else
        { //another write area entry:
          idxWriteAreaTest +=1; 
        }
      }
    }
  }
  STACKTRC_LEAVE; return bSufficing;
}



void* peek_ConcurrentRingBufferJcF(ConcurrentRingBufferJc const* ythis, int* nrofBytes) 
{ int nrofBytesAvailable;
  struct MemAreaC_t* read = ythis->read;   //this->read is non-volatile, because only 1 thread is allowed to read.
  struct MemAreaC_t* written = ythis->written;  //this->written is volatile, read 1 time and use it.
  STACKTRC_ENTRY("peek_ConcurrentRingBufferJcF");
  if(written >= read)
  { nrofBytesAvailable = offset_MemAreaC(read, written);
  }
  else
  { //returns only the first part from read to end, get the second part in a second call.
    nrofBytesAvailable = offset_MemAreaC(read, ythis->end);
  }
  *nrofBytes = nrofBytesAvailable;
  if(nrofBytesAvailable ==0){ read = null; } //nothing to read.
  else if(nrofBytesAvailable < 0)
  { THROW_s0(RuntimeException, "consistence error", nrofBytesAvailable);
  }
  STACKTRC_LEAVE; return read;
}


void free_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis, int nrofBytes) 
{ STACKTRC_ENTRY("free_ConcurrentRingBufferJcF");
  { struct MemAreaC_t* read = ythis->read;
    struct MemAreaC_t* written = ythis->written;
    struct MemAreaC_t* myReadNext = addOffset_MemAreaC(read, nrofBytes);
    if(written >= read)
    { if(written < myReadNext)
      { //this is a software error. It is illegal to free more bytes as there are readable.
        THROW_s0(IndexOutOfBoundsException, "to much bytes freeing", nrofBytes); 
      }
      else
      { ythis->read = myReadNext;
        //after them offer can write in the old read range.
      }
    }
    else //written < read, it means the read range wraps
    { if(myReadNext < ythis->end)  //NOTE: not <=, elsewhere read don't wrap.
      { //read is before end, the read area wraps still.
        ythis->read = myReadNext;  
        //after them offer can write in the old read range.
      }
      else
      { //myReadNext is >= ythis->end, than
        int nrofBytesToEnd = offset_MemAreaC(read, ythis->end);  //the bytes to end.
        nrofBytes -= nrofBytesToEnd;  //the rest from begin, typical 0 because peek supplies the bytes to ythis->end
        myReadNext = addOffset_MemAreaC(ythis->begin, nrofBytes);  //the new readNext wrapped.
        if(written < myReadNext)
        { //this is a software error. It is illegal to free more bytes as there are readable.
          THROW_s0(IndexOutOfBoundsException, "to much bytes freeing", nrofBytes); 
        }
        else
        { ythis->read = myReadNext;
          //after them offer can write in the old read range.
        }
      }
    }
  }
  STACKTRC_LEAVE;
}


/**
 * Not in Java, extension for C embedded systems.
 */
