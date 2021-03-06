/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.nano.swig;

public class WordRef {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected WordRef(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(WordRef obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        NanoJNIJNI.delete_WordRef(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setEnglish(String value) {
    NanoJNIJNI.WordRef_english_set(swigCPtr, this, value);
  }

  public String getEnglish() {
    return NanoJNIJNI.WordRef_english_get(swigCPtr, this);
  }

  public void setWord_class(String value) {
    NanoJNIJNI.WordRef_word_class_set(swigCPtr, this, value);
  }

  public String getWord_class() {
    return NanoJNIJNI.WordRef_word_class_get(swigCPtr, this);
  }

  public void setChinese(String value) {
    NanoJNIJNI.WordRef_chinese_set(swigCPtr, this, value);
  }

  public String getChinese() {
    return NanoJNIJNI.WordRef_chinese_get(swigCPtr, this);
  }

  public void setExample(String value) {
    NanoJNIJNI.WordRef_example_set(swigCPtr, this, value);
  }

  public String getExample() {
    return NanoJNIJNI.WordRef_example_get(swigCPtr, this);
  }

  public void setEnglish_inv(String value) {
    NanoJNIJNI.WordRef_english_inv_set(swigCPtr, this, value);
  }

  public String getEnglish_inv() {
    return NanoJNIJNI.WordRef_english_inv_get(swigCPtr, this);
  }

  public void setData_offset(long value) {
    NanoJNIJNI.WordRef_data_offset_set(swigCPtr, this, value);
  }

  public long getData_offset() {
    return NanoJNIJNI.WordRef_data_offset_get(swigCPtr, this);
  }

  public void setData_size(long value) {
    NanoJNIJNI.WordRef_data_size_set(swigCPtr, this, value);
  }

  public long getData_size() {
    return NanoJNIJNI.WordRef_data_size_get(swigCPtr, this);
  }

  public WordRef() {
    this(NanoJNIJNI.new_WordRef(), true);
  }

}
