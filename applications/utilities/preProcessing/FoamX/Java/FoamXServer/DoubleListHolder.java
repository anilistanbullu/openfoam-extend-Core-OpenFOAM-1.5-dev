package FoamXServer;


/**
* FoamXServer/DoubleListHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from FoamX.idl
* Thursday, April 10, 2008 11:16:12 PM BST
*/

public final class DoubleListHolder implements org.omg.CORBA.portable.Streamable
{
  public double value[] = null;

  public DoubleListHolder ()
  {
  }

  public DoubleListHolder (double[] initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = FoamXServer.DoubleListHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    FoamXServer.DoubleListHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return FoamXServer.DoubleListHelper.type ();
  }

}
