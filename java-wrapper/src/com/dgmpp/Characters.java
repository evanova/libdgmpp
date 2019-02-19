/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Characters {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Characters(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Characters obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Characters(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Characters() {
    this(dgmppJNI.new_Characters__SWIG_0(), true);
  }

  public Characters(long n) {
    this(dgmppJNI.new_Characters__SWIG_1(n), true);
  }

  public long size() {
    return dgmppJNI.Characters_size(swigCPtr, this);
  }

  public long capacity() {
    return dgmppJNI.Characters_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    dgmppJNI.Characters_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return dgmppJNI.Characters_isEmpty(swigCPtr, this);
  }

  public void clear() {
    dgmppJNI.Characters_clear(swigCPtr, this);
  }

  public void add(Character x) {
    dgmppJNI.Characters_add(swigCPtr, this, Character.getCPtr(x), x);
  }

  public Character get(int i) {
    long cPtr = dgmppJNI.Characters_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new Character(cPtr, false);
  }

  public void set(int i, Character val) {
    dgmppJNI.Characters_set(swigCPtr, this, i, Character.getCPtr(val), val);
  }

}
