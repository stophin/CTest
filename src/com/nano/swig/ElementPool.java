/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.nano.swig;

public class ElementPool {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected ElementPool(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ElementPool obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        NanoJNIJNI.delete_ElementPool(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setPool(MultiLinkElement value) {
    NanoJNIJNI.ElementPool_pool_set(swigCPtr, this, MultiLinkElement.getCPtr(value), value);
  }

  public MultiLinkElement getPool() {
    long cPtr = NanoJNIJNI.ElementPool_pool_get(swigCPtr, this);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public void setMap(SWIGTYPE_p_unsigned_char value) {
    NanoJNIJNI.ElementPool_map_set(swigCPtr, this, SWIGTYPE_p_unsigned_char.getCPtr(value));
  }

  public SWIGTYPE_p_unsigned_char getMap() {
    long cPtr = NanoJNIJNI.ElementPool_map_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_unsigned_char(cPtr, false);
  }

  public void setSize(int value) {
    NanoJNIJNI.ElementPool_size_set(swigCPtr, this, value);
  }

  public int getSize() {
    return NanoJNIJNI.ElementPool_size_get(swigCPtr, this);
  }

  public void setMsize(int value) {
    NanoJNIJNI.ElementPool_msize_set(swigCPtr, this, value);
  }

  public int getMsize() {
    return NanoJNIJNI.ElementPool_msize_get(swigCPtr, this);
  }

  public void setCount(int value) {
    NanoJNIJNI.ElementPool_count_set(swigCPtr, this, value);
  }

  public int getCount() {
    return NanoJNIJNI.ElementPool_count_get(swigCPtr, this);
  }

  public void setAt(SWIGTYPE_p_f_p_ElementPool_int__p_MultiLinkElement value) {
    NanoJNIJNI.ElementPool_at_set(swigCPtr, this, SWIGTYPE_p_f_p_ElementPool_int__p_MultiLinkElement.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_ElementPool_int__p_MultiLinkElement getAt() {
    long cPtr = NanoJNIJNI.ElementPool_at_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_ElementPool_int__p_MultiLinkElement(cPtr, false);
  }

  public void setGet(SWIGTYPE_p_f_p_ElementPool__p_MultiLinkElement value) {
    NanoJNIJNI.ElementPool_get_set(swigCPtr, this, SWIGTYPE_p_f_p_ElementPool__p_MultiLinkElement.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_ElementPool__p_MultiLinkElement getGet() {
    long cPtr = NanoJNIJNI.ElementPool_get_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_ElementPool__p_MultiLinkElement(cPtr, false);
  }

  public void setBack(SWIGTYPE_p_f_p_ElementPool_p_MultiLinkElement__void value) {
    NanoJNIJNI.ElementPool_back_set(swigCPtr, this, SWIGTYPE_p_f_p_ElementPool_p_MultiLinkElement__void.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_ElementPool_p_MultiLinkElement__void getBack() {
    long cPtr = NanoJNIJNI.ElementPool_back_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_ElementPool_p_MultiLinkElement__void(cPtr, false);
  }

  public ElementPool() {
    this(NanoJNIJNI.new_ElementPool(), true);
  }

}
