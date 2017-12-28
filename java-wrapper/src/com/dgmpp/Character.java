/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Character extends Type {
  private transient long swigCPtr;

  protected Character(long cPtr, boolean cMemoryOwn) {
    super(dgmppJNI.Character_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Character obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Character(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Ship ship() {
    long cPtr = dgmppJNI.Character_ship__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Ship(cPtr, false);
  }

  public Ship ship(int typeID) {
    long cPtr = dgmppJNI.Character_ship__SWIG_1(swigCPtr, this, typeID);
    return (cPtr == 0) ? null : new Ship(cPtr, false);
  }

  public Structure structure() {
    long cPtr = dgmppJNI.Character_structure__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Structure(cPtr, false);
  }

  public Structure structure(int typeID) {
    long cPtr = dgmppJNI.Character_structure__SWIG_1(swigCPtr, this, typeID);
    return (cPtr == 0) ? null : new Structure(cPtr, false);
  }

  public void setSkillLevels(int level) {
    dgmppJNI.Character_setSkillLevels(swigCPtr, this, level);
  }

  public boolean factorReload() {
    return dgmppJNI.Character_factorReload(swigCPtr, this);
  }

  public Implant addImplant(int typeID, boolean replace) {
    long cPtr = dgmppJNI.Character_addImplant__SWIG_0(swigCPtr, this, typeID, replace);
    return (cPtr == 0) ? null : new Implant(cPtr, false);
  }

  public Implant addImplant(int typeID) {
    long cPtr = dgmppJNI.Character_addImplant__SWIG_1(swigCPtr, this, typeID);
    return (cPtr == 0) ? null : new Implant(cPtr, false);
  }

  public Booster addBooster(int typeID, boolean replace) {
    long cPtr = dgmppJNI.Character_addBooster__SWIG_0(swigCPtr, this, typeID, replace);
    return (cPtr == 0) ? null : new Booster(cPtr, false);
  }

  public Booster addBooster(int typeID) {
    long cPtr = dgmppJNI.Character_addBooster__SWIG_1(swigCPtr, this, typeID);
    return (cPtr == 0) ? null : new Booster(cPtr, false);
  }

  public void remove(Implant implant) {
    dgmppJNI.Character_remove__SWIG_0(swigCPtr, this, Implant.getCPtr(implant), implant);
  }

  public void remove(Booster booster) {
    dgmppJNI.Character_remove__SWIG_1(swigCPtr, this, Booster.getCPtr(booster), booster);
  }

  public Skills skills() {
    return new Skills(dgmppJNI.Character_skills(swigCPtr, this), true);
  }

  public Implants implants() {
    return new Implants(dgmppJNI.Character_implants(swigCPtr, this), true);
  }

  public Boosters boosters() {
    return new Boosters(dgmppJNI.Character_boosters(swigCPtr, this), true);
  }

  public Implant implant(int slot) {
    long cPtr = dgmppJNI.Character_implant(swigCPtr, this, slot);
    return (cPtr == 0) ? null : new Implant(cPtr, false);
  }

  public Booster booster(int slot) {
    long cPtr = dgmppJNI.Character_booster(swigCPtr, this, slot);
    return (cPtr == 0) ? null : new Booster(cPtr, false);
  }

  public double droneControlDistance() {
    return dgmppJNI.Character_droneControlDistance(swigCPtr, this);
  }

}
