package FoamXServer;


/**
* FoamXServer/HostDescriptor.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from FoamX.idl
* Thursday, April 10, 2008 11:16:12 PM BST
*/

public final class HostDescriptor implements org.omg.CORBA.portable.IDLEntity
{
  public String name = null;
  public boolean alive = false;

  public HostDescriptor ()
  {
  } // ctor

  public HostDescriptor (String _name, boolean _alive)
  {
    name = _name;
    alive = _alive;
  } // ctor

} // class HostDescriptor
