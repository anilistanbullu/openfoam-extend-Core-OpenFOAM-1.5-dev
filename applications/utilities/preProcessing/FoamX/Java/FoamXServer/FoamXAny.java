package FoamXServer;


/**
* FoamXServer/FoamXAny.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from FoamX.idl
* Thursday, April 10, 2008 11:16:12 PM BST
*/

public final class FoamXAny implements org.omg.CORBA.portable.IDLEntity
{
  public FoamXServer.FoamXType type = null;
  public org.omg.CORBA.Any value = null;

  public FoamXAny ()
  {
  } // ctor

  public FoamXAny (FoamXServer.FoamXType _type, org.omg.CORBA.Any _value)
  {
    type = _type;
    value = _value;
  } // ctor

} // class FoamXAny
