set(utility_srcs
	Date.cc
	Date.h
	FileUtil.cc
	FileUtil.h
	LogFile.cc
	LogFile.h
	Logging.cc
	Logging.h
	LogStream.cc
	LogStream.h
	Timestamp.cc
	Timestamp.h
	Thread.cc
	Thread.h
	#Measure.cc
	#Measure.h
	#ReadIni.cc
	#ReadIni.h
	#SPSCQueue.h
    itoa.h
	itoa.cc
	Types.h	
	Utility.h
	Compatible.h
	AsyncLogging.cc
	AsyncLogging.h
	#FlowReader.h
	#Flow.h
	#CacheNode.cc
	#CacheNode.h
	#CacheNodeList.cc
	#CacheNodeList.h
	Semaphore.cc
	Semaphore.h
	WeakCallback.h
	#AutoCleanHelper.cc
	#AutoCleanHelper.h
	#HeadView.cc
	#HeadView.h
	#DirHandler.cc
	#DirHandler.h
	CountDownLatch.cc
	CountDownLatch.h
  )

add_library(utility STATIC ${utility_srcs})

if(UNIX)
target_link_libraries(utility pthread rt)
set_target_properties(utility PROPERTIES COMPILE_FLAGS "-std=c++11")

endif(UNIX)

