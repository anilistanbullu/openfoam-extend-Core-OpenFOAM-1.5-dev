package FoamXServer;


/**
* FoamXServer/StringPair.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from FoamX.idl
* Thursday, April 10, 2008 11:16:12 PM BST
*/

public final class StringPair implements org.omg.CORBA.portable.IDLEntity
{
  public String name = null;
  public String value = null;

  public StringPair ()
  {
  } // ctor

  public StringPair (String _name, String _value)
  {
    name = _name;
    value = _value;
  } // ctor

} // class StringPair
