package FoamXServer;

/**
* FoamXServer/MessageTypeHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from PatchTool.idl
* Friday, September 7, 2007 12:01:26 AM BST
*/

public final class MessageTypeHolder implements org.omg.CORBA.portable.Streamable
{
  public FoamXServer.MessageType value = null;

  public MessageTypeHolder ()
  {
  }

  public MessageTypeHolder (FoamXServer.MessageType initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = FoamXServer.MessageTypeHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    FoamXServer.MessageTypeHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return FoamXServer.MessageTypeHelper.type ();
  }

}
