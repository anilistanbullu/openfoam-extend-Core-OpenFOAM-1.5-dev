package FoamXServer;


/**
* FoamXServer/ApplicationClassDescriptorListHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from PatchTool.idl
* Friday, September 7, 2007 12:01:26 AM BST
*/

public final class ApplicationClassDescriptorListHolder implements org.omg.CORBA.portable.Streamable
{
  public FoamXServer.ApplicationClassDescriptor value[] = null;

  public ApplicationClassDescriptorListHolder ()
  {
  }

  public ApplicationClassDescriptorListHolder (FoamXServer.ApplicationClassDescriptor[] initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = FoamXServer.ApplicationClassDescriptorListHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    FoamXServer.ApplicationClassDescriptorListHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return FoamXServer.ApplicationClassDescriptorListHelper.type ();
  }

}
