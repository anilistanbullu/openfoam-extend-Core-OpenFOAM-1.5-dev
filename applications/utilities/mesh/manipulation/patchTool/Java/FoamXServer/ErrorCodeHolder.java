package FoamXServer;

/**
* FoamXServer/ErrorCodeHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from PatchTool.idl
* Friday, September 7, 2007 12:01:26 AM BST
*/

public final class ErrorCodeHolder implements org.omg.CORBA.portable.Streamable
{
  public FoamXServer.ErrorCode value = null;

  public ErrorCodeHolder ()
  {
  }

  public ErrorCodeHolder (FoamXServer.ErrorCode initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = FoamXServer.ErrorCodeHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    FoamXServer.ErrorCodeHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return FoamXServer.ErrorCodeHelper.type ();
  }

}
