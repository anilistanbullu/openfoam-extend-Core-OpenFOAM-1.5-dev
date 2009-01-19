package FoamXServer;


/**
* FoamXServer/FoamXSYSErrorHelper.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from PatchTool.idl
* Friday, September 7, 2007 12:01:26 AM BST
*/


// Invalid remote system invocation (e.g. machine can't be reached)
abstract public class FoamXSYSErrorHelper
{
  private static String  _id = "IDL:FoamXServer/FoamXSYSError:1.0";

  public static void insert (org.omg.CORBA.Any a, FoamXServer.FoamXSYSError that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static FoamXServer.FoamXSYSError extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  private static boolean __active = false;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      synchronized (org.omg.CORBA.TypeCode.class)
      {
        if (__typeCode == null)
        {
          if (__active)
          {
            return org.omg.CORBA.ORB.init().create_recursive_tc ( _id );
          }
          __active = true;
          org.omg.CORBA.StructMember[] _members0 = new org.omg.CORBA.StructMember [6];
          org.omg.CORBA.TypeCode _tcOf_members0 = null;
          _tcOf_members0 = FoamXServer.ErrorCodeHelper.type ();
          _members0[0] = new org.omg.CORBA.StructMember (
            "errorCode",
            _tcOf_members0,
            null);
          _tcOf_members0 = org.omg.CORBA.ORB.init ().create_string_tc (0);
          _members0[1] = new org.omg.CORBA.StructMember (
            "errorMessage",
            _tcOf_members0,
            null);
          _tcOf_members0 = org.omg.CORBA.ORB.init ().create_string_tc (0);
          _members0[2] = new org.omg.CORBA.StructMember (
            "hostName",
            _tcOf_members0,
            null);
          _tcOf_members0 = org.omg.CORBA.ORB.init ().create_string_tc (0);
          _members0[3] = new org.omg.CORBA.StructMember (
            "methodName",
            _tcOf_members0,
            null);
          _tcOf_members0 = org.omg.CORBA.ORB.init ().create_string_tc (0);
          _members0[4] = new org.omg.CORBA.StructMember (
            "fileName",
            _tcOf_members0,
            null);
          _tcOf_members0 = org.omg.CORBA.ORB.init ().get_primitive_tc (org.omg.CORBA.TCKind.tk_long);
          _members0[5] = new org.omg.CORBA.StructMember (
            "lineNo",
            _tcOf_members0,
            null);
          __typeCode = org.omg.CORBA.ORB.init ().create_exception_tc (FoamXServer.FoamXSYSErrorHelper.id (), "FoamXSYSError", _members0);
          __active = false;
        }
      }
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static FoamXServer.FoamXSYSError read (org.omg.CORBA.portable.InputStream istream)
  {
    FoamXServer.FoamXSYSError value = new FoamXServer.FoamXSYSError ();
    // read and discard the repository ID
    istream.read_string ();
    value.errorCode = FoamXServer.ErrorCodeHelper.read (istream);
    value.errorMessage = istream.read_string ();
    value.hostName = istream.read_string ();
    value.methodName = istream.read_string ();
    value.fileName = istream.read_string ();
    value.lineNo = istream.read_long ();
    return value;
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, FoamXServer.FoamXSYSError value)
  {
    // write the repository ID
    ostream.write_string (id ());
    FoamXServer.ErrorCodeHelper.write (ostream, value.errorCode);
    ostream.write_string (value.errorMessage);
    ostream.write_string (value.hostName);
    ostream.write_string (value.methodName);
    ostream.write_string (value.fileName);
    ostream.write_long (value.lineNo);
  }

}
