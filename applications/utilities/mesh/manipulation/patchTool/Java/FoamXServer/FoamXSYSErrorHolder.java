package FoamXServer;

/**
* FoamXServer/FoamXSYSErrorHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from PatchTool.idl
* Friday, September 7, 2007 12:01:26 AM BST
*/


// Invalid remote system invocation (e.g. machine can't be reached)
public final class FoamXSYSErrorHolder implements org.omg.CORBA.portable.Streamable
{
  public FoamXServer.FoamXSYSError value = null;

  public FoamXSYSErrorHolder ()
  {
  }

  public FoamXSYSErrorHolder (FoamXServer.FoamXSYSError initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = FoamXServer.FoamXSYSErrorHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    FoamXServer.FoamXSYSErrorHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return FoamXServer.FoamXSYSErrorHelper.type ();
  }

}
