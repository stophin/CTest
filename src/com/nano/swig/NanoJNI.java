/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.nano.swig;

public class NanoJNI implements NanoJNIConstants {
  public static long getuid() {
    return NanoJNIJNI.getuid();
  }

  public static double CTest_getTest(SWIGTYPE_p_CTest that, double line, double row) {
    return NanoJNIJNI.CTest_getTest(SWIGTYPE_p_CTest.getCPtr(that), line, row);
  }

  public static double CTest_getSum(SWIGTYPE_p_CTest that, double sum) {
    return NanoJNIJNI.CTest_getSum(SWIGTYPE_p_CTest.getCPtr(that), sum);
  }

  public static void _CTest(SWIGTYPE_p_CTest that) {
    NanoJNIJNI._CTest(SWIGTYPE_p_CTest.getCPtr(that));
  }

  public static String Start() {
    return NanoJNIJNI.Start();
  }

  public static int Prepare(byte[] buff, int len) {
    return NanoJNIJNI.Prepare(buff, len);
  }

  public static int Manipluate(byte[] buff, int len, int plink) {
    return NanoJNIJNI.Manipluate(buff, len, plink);
  }

  public static int IteratorStart() {
    return NanoJNIJNI.IteratorStart();
  }

  public static int IteratorFetch() {
    return NanoJNIJNI.IteratorFetch();
  }

  public static int IteratorGet(int index) {
    return NanoJNIJNI.IteratorGet(index);
  }

  public static int IteratorNext() {
    return NanoJNIJNI.IteratorNext();
  }

  public static int Iterator(String buff) {
    return NanoJNIJNI.Iterator(buff);
  }

  public static int Search(String word) {
    return NanoJNIJNI.Search(word);
  }

  public static String Result_Prepare() {
    return NanoJNIJNI.Result_Prepare();
  }

  public static String Result() {
    return NanoJNIJNI.Result();
  }

  public static String Result_Trans(int pos) {
    return NanoJNIJNI.Result_Trans(pos);
  }

  public static String Result_Examp(int pos) {
    return NanoJNIJNI.Result_Examp(pos);
  }

  public static void MultiLinkElement_clear(MultiLinkElement that) {
    NanoJNIJNI.MultiLinkElement_clear(MultiLinkElement.getCPtr(that), that);
  }

  public static MultiLinkElement MultiLinkElement_free(MultiLinkElement that) {
    long cPtr = NanoJNIJNI.MultiLinkElement_free(MultiLinkElement.getCPtr(that), that);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public static void _MultiLinkElement(MultiLinkElement that, int linkcount) {
    NanoJNIJNI._MultiLinkElement(MultiLinkElement.getCPtr(that), that, linkcount);
  }

  public static MultiLinkElement MultiLinkBase_removeLink(MultiLinkBase that, MultiLinkElement link) {
    long cPtr = NanoJNIJNI.MultiLinkBase_removeLink(MultiLinkBase.getCPtr(that), that, MultiLinkElement.getCPtr(link), link);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public static MultiLinkElement MultiLinkBase_get(MultiLinkBase that, int index) {
    long cPtr = NanoJNIJNI.MultiLinkBase_get(MultiLinkBase.getCPtr(that), that, index);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public static void MultiLinkBase_insertLink(MultiLinkBase that, MultiLinkElement link, MultiLinkElement before, MultiLinkElement after) {
    NanoJNIJNI.MultiLinkBase_insertLink(MultiLinkBase.getCPtr(that), that, MultiLinkElement.getCPtr(link), link, MultiLinkElement.getCPtr(before), before, MultiLinkElement.getCPtr(after), after);
  }

  public static MultiLinkElement MultiLinkBase_prev(MultiLinkBase that, MultiLinkElement link) {
    long cPtr = NanoJNIJNI.MultiLinkBase_prev(MultiLinkBase.getCPtr(that), that, MultiLinkElement.getCPtr(link), link);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public static MultiLinkElement MultiLinkBase_next(MultiLinkBase that, MultiLinkElement link) {
    long cPtr = NanoJNIJNI.MultiLinkBase_next(MultiLinkBase.getCPtr(that), that, MultiLinkElement.getCPtr(link), link);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public static void _MultiLinkBase(MultiLinkBase that, int linkindex) {
    NanoJNIJNI._MultiLinkBase(MultiLinkBase.getCPtr(that), that, linkindex);
  }

  public static MultiLinkElement ElementPool_at(ElementPool that, int index) {
    long cPtr = NanoJNIJNI.ElementPool_at(ElementPool.getCPtr(that), that, index);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public static MultiLinkElement ElementPool_get(ElementPool that) {
    long cPtr = NanoJNIJNI.ElementPool_get(ElementPool.getCPtr(that), that);
    return (cPtr == 0) ? null : new MultiLinkElement(cPtr, false);
  }

  public static void ElementPool_back(ElementPool that, MultiLinkElement o) {
    NanoJNIJNI.ElementPool_back(ElementPool.getCPtr(that), that, MultiLinkElement.getCPtr(o), o);
  }

  public static void _ElementPool(ElementPool that, MultiLinkElement pool, SWIGTYPE_p_unsigned_char map, int size) {
    NanoJNIJNI._ElementPool(ElementPool.getCPtr(that), that, MultiLinkElement.getCPtr(pool), pool, SWIGTYPE_p_unsigned_char.getCPtr(map), size);
  }

}
