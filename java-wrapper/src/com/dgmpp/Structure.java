/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Structure extends Ship {
  private transient long swigCPtr;

  protected Structure(long cPtr, boolean cMemoryOwn) {
    super(dgmppJNI.Structure_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Structure obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Structure(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Structure(int typeID) {
    this(dgmppJNI.new_Structure(typeID), true);
  }

  public int fuelBlockTypeID() {
    return dgmppJNI.Structure_fuelBlockTypeID(swigCPtr, this);
  }

  public UnitsPerHour fuelUse() {
    return new UnitsPerHour(dgmppJNI.Structure_fuelUse(swigCPtr, this), true);
  }

}
