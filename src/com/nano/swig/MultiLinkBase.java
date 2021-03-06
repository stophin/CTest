/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.nano.swig;

public class MultiLinkBase {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected MultiLinkBase(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(MultiLinkBase obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        NanoJNIJNI.delete_MultiLinkBase(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setLinkcount(int value) {
    NanoJNIJNI.MultiLinkBase_linkcount_set(swigCPtr, this, value);
  }

  public int getLinkcount() {
    return NanoJNIJNI.MultiLinkBase_linkcount_get(swigCPtr, this);
  }

  public void setLinkindex(int value) {
    NanoJNIJNI.MultiLinkBase_linkindex_set(swigCPtr, this, value);
  }

  public int getLinkindex() {
    return NanoJNIJNI.MultiLinkBase_linkindex_get(swigCPtr, this);
  }

  public void setLink(MultiLinkElement value) {
    NanoJNIJNI.MultiLinkBase_link_set(swigCPtr, this, MultiLinkElement.getCPtr(value), value);
  }

  public MultiLinkElement getLink() {
    long cPtr = NanoJNIJNI.MultiLinkBase_link_get(swigCPtr, this);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public void setInsertLink(SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement_p_MultiLinkElement_p_MultiLinkElement__void value) {
    NanoJNIJNI.MultiLinkBase_insertLink_set(swigCPtr, this, SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement_p_MultiLinkElement_p_MultiLinkElement__void.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement_p_MultiLinkElement_p_MultiLinkElement__void getInsertLink() {
    long cPtr = NanoJNIJNI.MultiLinkBase_insertLink_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement_p_MultiLinkElement_p_MultiLinkElement__void(cPtr, false);
  }

  public void setRemoveLink(SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement value) {
    NanoJNIJNI.MultiLinkBase_removeLink_set(swigCPtr, this, SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement getRemoveLink() {
    long cPtr = NanoJNIJNI.MultiLinkBase_removeLink_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement(cPtr, false);
  }

  public void setGet(SWIGTYPE_p_f_p_MultiLinkBase_int__p_MultiLinkElement value) {
    NanoJNIJNI.MultiLinkBase_get_set(swigCPtr, this, SWIGTYPE_p_f_p_MultiLinkBase_int__p_MultiLinkElement.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_MultiLinkBase_int__p_MultiLinkElement getGet() {
    long cPtr = NanoJNIJNI.MultiLinkBase_get_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_MultiLinkBase_int__p_MultiLinkElement(cPtr, false);
  }

  public void setPrev(SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement value) {
    NanoJNIJNI.MultiLinkBase_prev_set(swigCPtr, this, SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement getPrev() {
    long cPtr = NanoJNIJNI.MultiLinkBase_prev_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement(cPtr, false);
  }

  public void setNext(SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement value) {
    NanoJNIJNI.MultiLinkBase_next_set(swigCPtr, this, SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement getNext() {
    long cPtr = NanoJNIJNI.MultiLinkBase_next_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_MultiLinkBase_p_MultiLinkElement__p_MultiLinkElement(cPtr, false);
  }

  public MultiLinkBase() {
    this(NanoJNIJNI.new_MultiLinkBase(), true);
  }

}
