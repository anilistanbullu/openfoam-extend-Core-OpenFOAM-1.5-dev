package FoamXServer.CasePostServer;


/**
* FoamXServer/CasePostServer/ICasePostServerOperations.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from FoamX.idl
* Thursday, April 10, 2008 11:16:12 PM BST
*/


// ---------------------------------------------------------------------
public interface ICasePostServerOperations 
{

  // Attributes.
  String caseRoot ();
  String caseName ();
  int nProcs ();

  // Time-steps.
  String[] availableTimeSteps ();

  // Set database
  void setTime (String timeName, int timeIndex) throws FoamXServer.FoamXError, FoamXServer.FoamXIOError;

  // Slave variant
  void setTimeSlave ();

  // Get patchnames over all domains
  String[] getPatchNames () throws FoamXServer.FoamXError, FoamXServer.FoamXIOError;

  // Slave variant
  void getPatchNamesSlave ();

  // Get fieldNames
  String[] getFieldNames (String type) throws FoamXServer.FoamXError, FoamXServer.FoamXIOError;

  // Bounding box
  void getMeshBb (FoamXServer.Point3Holder min, FoamXServer.Point3Holder max) throws FoamXServer.FoamXError;

  // Slave variant
  void getMeshBbSlave ();

  // Patch mesh
  void getPatchMesh (String patchName, double creaseAngle, FoamXServer.FloatListHolder points, FoamXServer.LongListHolder edges) throws FoamXServer.FoamXError;

  // Slave variant
  void getPatchMeshSlave ();

  // Cut mesh
  void getCutMesh (float[] basePoint, float[] normal, FoamXServer.FloatListHolder points, FoamXServer.LongListHolder edges) throws FoamXServer.FoamXError;

  // Slave variant
  void getCutMeshSlave ();

  // Cut mesh outline
  void getCutMeshOutline (float[] basePoint, float[] normal, FoamXServer.FloatListHolder points, FoamXServer.LongListHolder edges) throws FoamXServer.FoamXError;

  // Slave variant
  void getCutMeshOutlineSlave ();

  // Triangulate and sample patch
  void getTriPatch (String fieldName, String patchName, FoamXServer.FloatListHolder points, FoamXServer.LongListHolder triFaces, FoamXServer.FloatListHolder values) throws FoamXServer.FoamXError, FoamXServer.FoamXIOError;

  // Slave variant
  void getTriPatchSlave ();

  // Triangulate and sample patch
  void getTriPatchVec (String fieldName, String patchName, FoamXServer.FloatListHolder points, FoamXServer.LongListHolder triFaces, FoamXServer.FloatListHolder values) throws FoamXServer.FoamXError, FoamXServer.FoamXIOError;

  // Slave variant
  void getTriPatchVecSlave ();

  // Cutplane and sample
  void cutPlane (String fieldName, float[] basePoint, float[] normal, FoamXServer.FloatListHolder points, FoamXServer.LongListHolder triFaces, FoamXServer.FloatListHolder values) throws FoamXServer.FoamXError, FoamXServer.FoamXIOError;

  // Slave variant
  void cutPlaneSlave ();

  // Cutplane and sample
  void cutPlaneVec (String fieldName, float[] basePoint, float[] normal, FoamXServer.FloatListHolder points, FoamXServer.LongListHolder triFaces, FoamXServer.FloatListHolder values) throws FoamXServer.FoamXError, FoamXServer.FoamXIOError;

  // Slave variant
  void cutPlaneVecSlave ();

  //- Lifetime management.
  void close ();
} // interface ICasePostServerOperations
