/* Module name */
%module NanoJNI


/*  
 * char *BYTE typemaps.  
 * These are input typemaps for mapping a Java byte[] array to a C char array. 
 * Note that as a Java array is used and thus passeed by reference, the C routine  
 * can return data to Java via the parameter. 
 * 
 * Example usage wrapping: 
 *   void foo(char *array); 
 *   
 * Java usage: 
 *   byte b[] = new byte[20]; 
 *   modulename.foo(b); 
 */ 
%typemap(jni) char *BYTE "jbyteArray" 
%typemap(jtype) char *BYTE "byte[]" 
%typemap(jstype) char *BYTE "byte[]" 
%typemap(in) char *BYTE { 
  $1 = (char *) JCALL2(GetByteArrayElements, jenv, $input, 0);  
} 
 
%typemap(argout) char *BYTE { 
  JCALL3(ReleaseByteArrayElements, jenv, $input, (jbyte *) $1, 0);  
} 
 
%typemap(javain) char *BYTE "$javainput" 
 
/* Prevent default freearg typemap from being used */ 
%typemap(freearg) char *BYTE "" 
 
 


/* 
 * unsigned char *NIOBUFFER typemaps. 
 * This is for mapping Java nio buffers to C char arrays.
 * It is useful for performance critical code as it reduces the memory copy an marshaling overhead.
 * Note: The Java buffer has to be allocated with allocateDirect.
 *
 * Example usage wrapping:
 *   %apply unsigned char *NIOBUFFER { unsigned char *buf };
 *   void foo(unsigned char *buf);
 *  
 * Java usage:
 *   java.nio.ByteBuffer b = ByteBuffer.allocateDirect(20); 
 *   modulename.foo(b);
 */
%typemap(jni) unsigned char *NIOBUFFER "jobject"  
%typemap(jtype) unsigned char *NIOBUFFER "java.nio.ByteBuffer"  
%typemap(jstype) unsigned char *NIOBUFFER "java.nio.ByteBuffer"  
%typemap(javain,
  pre="  assert $javainput.isDirect() : \"Buffer must be allocated direct.\";") unsigned char *NIOBUFFER "$javainput"
%typemap(javaout) unsigned char *NIOBUFFER {  
  return $jnicall;  
}  
%typemap(in) unsigned char *NIOBUFFER {  
  $1 = (unsigned char *) JCALL1(GetDirectBufferAddress, jenv, $input); 
  if ($1 == NULL) {  
    SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, "Unable to get address of a java.nio.ByteBuffer direct byte buffer. Buffer must be a direct buffer and not a non-direct buffer.");  
  }  
}  
%typemap(memberin) unsigned char *NIOBUFFER {  
  if ($input) {  
    $1 = $input;  
  } else {  
    $1 = 0;  
  }  
}  
%typemap(freearg) unsigned char *NIOBUFFER ""  






%apply  char *BYTE {  char *buf };
%apply char *BYTE { char *data };
%apply unsigned char *NIOBUFFER { unsigned char *data};

%{
/* POSIX system API */
#include <unistd.h>

#include <src\CTest.c>
#include <src\MultiLink.c>
%}

/* uid_t */
typedef unsigned int uid_t;

/* Wrap getuid */
extern uid_t getuid(void);


%include <src\CTest.h>
%include <src\MultiLink.h>
