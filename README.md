# CTest  
CTest: A dictionary made of Android NDK&amp;JNI to search for reversal English words.  
  
  Example:  Search English words end with "or"  
    visitor  
    razor  
    mayor  
    ...  
    
    
# HOWTO 
--  
1.  
Download Eclipse Luna, with jdk1.8.0_144  
2.  
Download ADT-23.0.6.zip, and use eclipse->Help->Install New SoftWare to add the ADT.  
This may take few minutes.  
3.  
Download android-sdk_r24.4.1-windows,   
and set Eclipse->Window->Preferences->Android->SDK Location when asked.  
3.  
Download android-ndk-r14b-windows-x86_64,  
and set Eclipse->Window->Preferences->Android->NDK->NDK Location   
to the /build/ directory of the NDK downloaded.  
Right click project name->Android Tools->Add Native Support...,  
make sure that "lib" + project name + ".so" is added to the library.  
4.  
Download swigwin-3.0.12, and open Run->External Tools->External Tools Configurations...,  
create a new Program, set it's Location to the swig downloaded, and choose swig.exe.  
And then set Working Directory as ${project_loc} and Arguments as the following:  
-c++ -java -package com.nano.swig -outdir src/com/nano/swig jni/Unix.i  
Means swig compiles C++ source code to java, from /jni/ folder to /src/com/nano/swig/ folder, with class name com.nano.swig and  configuration file jni/Unix.i.  
Please refer to /jni/README.md to konw how to write jni files.  
Once finished the jni files, run this external program to build the files.   
Checkout the java files compiled in /src/com/nano/swig folder.  
5.  
Using android-ndk-r14b-windows-x86_64/ndk-build to build the C++ files in /jni/ folder,   
to generate lib file in /lib/ folder.  
6.  
Find the java file in /src/com/nano/swig with the name which was configured in /jni/Android.mk  
and marked as LOCAL_MODULE, which should be LOCAL_MODULE + "JNI.java", say NanoJNIJNI.java,  
open it and add the lib to load:  
static{  
  System.loadLibrary("NanoJNI");//here is the LOCAL_MODULE in Android.mk  
}  
Though set the load lib code here is OK, but when java is regenerated, this code is gone.  
I suggest add it in the MainActivity.java, so that I won't reconfigure it again.  
7.  
Make AVD:  
Open android-sdk_r24.4.1-windows/SDK Manager, and download Android System Image.  
Choose Android 6.0(API 23)->ARM EABI v7a System Image & Intel x86 Atom System Image(or Atom_64)  
and install packages.  
Then open android-sdk_r24.4.1-windows/AVD Manager, make an available AVD.  
8.  
Right click project name->Android Tools->Export Singned/Unsigned Application Packge  
to export standard apk file in /bin/ folder.  
  
  
Problems:  
1.Multiple markers at this line  
  - Syntax error  
  - Type 'JNIEnv' could not be resolved  
  - Type 'JNICALL' could not be resolved  
  When encountered this problem, use Project->Properties->C/C++ General->  
  Path and Symbols, and select include tab, Add->  
  $Android_NDK_HOME/platforms/android-14/arch-arm/usr/include  
  
2.You may need to set proxy to dl.google.com/dl-ssl.google.com  
	Please use the following proxy:  
	mirrors.neusoft.edu.cn:80  
	
3.Once you generated java & cxx file using swig, all the char * type in c/cpp file  
   will be transformed to jstring in cxx, and String in java by default.  
   When you actually needed a byte[] instead of a String type in java  
   (eg. when reading raw file in binary format),  
   you can do the following:  
   - change cxx file: jstring ---> jbyteArray  
   - jenv->GetStringUTFChars ---> jenv->GetByteArrayElements  
   - jenv->ReleaseStringUTFChars ---> jenv->ReleaseByteArrayElements  
   - note the parameters are different  
   - change java file: String ---> byte[]  
   - redo step 5 to rebuild proper lib for jni  
   
  
  # Preview  
  ![Alt text](https://github.com/stophin/CTest/blob/master/Preview.jpg)  