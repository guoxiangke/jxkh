<?php

/**
 *  Create a new directory
 *
 */
function filevault_create_directory($path){

  global $user;
  $newDir = basename($path);
  $parent = dirname($path);

  // Do you have access to write in this dir?
  $parent_id = db_query('SELECT {filevault_path}.id
                      FROM {filevault_path}
                      LEFT JOIN {filevault_access}
                      ON ({filevault_path}.id = {filevault_access}.filevault_path_id)
                      WHERE {filevault_path}.path = :path
                      AND {filevault_path}.uid = :uid
                      AND {filevault_path}.uid = {filevault_access}.uid
                      AND {filevault_access}.create_access = 1', array(':path' =>$parent, ':uid' => $user->uid))
                      ->fetchAll();

  // Access denied
  if( count($parent_id) == 0 ){
    return "Access denied: ".$parent;
  }

  // Okay you have access. Is there a file or directory with this name
  // in the directory already?
  $path_id = db_query('SELECT {filevault_path}.id
                       FROM {filevault_path}
                       WHERE path = :path', array(':path' =>$path))
                       ->fetchAll();

  // Sorry, there is a file object with that name
  if( count($path_id) != 0 ){
    return "File exites";
  }

  // Everything is cool, let's create that directory

  // insert in the path table
  $path_id    =   db_insert('filevault_path')
                      ->fields(array(
                        'id' => NULL,
                        'uid' => $user->uid,
                        'path' => $path,
                        ))
                      ->execute();

  // insert in the tree table with the parent as id.
  $tree_id    =   db_insert('filevault_tree')
                      ->fields(array(
                        'filevault_path_id' => $parent_id[0]->id,
                        'name' => $newDir,
                        'type' =>'D',
                        'updated' => REQUEST_TIME,
                        'created' => REQUEST_TIME,
                        ))
                      ->execute();

  // Give the uploader full access
  $access_id  =   db_insert('filevault_access')
                      ->fields(array(
                        'filevault_path_id' => $path_id,
                        'uid' => $user->uid,
                        'create_access' => 1,
                        'read_access' => 1,
                        'update_access' => 1,
                        'delete_access' => 1,
                        ))
                      ->execute();

  return "success";
}



/**
 *  Create a new file
 *
 */

function filevault_create_file($name, $data){

  global $user;
  $newFileName = basename($name);
  $parent = dirname($name);

  // Do you have access to write in this dir?
  $parent_id = db_query('SELECT {filevault_path}.id
                      FROM {filevault_path}
                      LEFT JOIN {filevault_access}
                      ON ({filevault_path}.id = {filevault_access}.filevault_path_id)
                      WHERE {filevault_path}.path = :path
                      AND {filevault_path}.uid = :uid
                      AND {filevault_path}.uid = {filevault_access}.uid
                      AND {filevault_access}.create_access = 1', array(':path' =>$parent, ':uid' => $user->uid))
                      ->fetchAll();

  // Access denied
  if( count($parent_id) == 0 ){
    return "Access denied: ".$parent;
  }

  // Okay you have access. Is there a file or directory with this name
  // in the directory already?
  $path_id = db_query('SELECT {filevault_path}.id
                       FROM {filevault_path}
                       WHERE path = :path', array(':path' =>$name))
                       ->fetchAll();

  // Sorry, there is a file object with that name
  if( count($path_id) != 0 ){
    return "File exites";
  }

  // Everything is cool, let's create that file
  $file = file_save_data($data,'temporary://'.$newFileName);

  if ($file) {
    if ($file = file_move($file, 'public://')) {

        // Create the entity template
        $entity = array();
        $entity['id'] = 0;
        $entity['vid'] = 0;
        $entity['filename'] = $file->filename;
        $entity['size'] = $file->filesize;
        $entity['mime_type'] = $file->filemime;
        $entity['uri'] = $file->uri;
        $entity['fid'] = intval($file->fid);
        $entity['md5'] = "Not implement yet";
        $entity['mime_type'] = $file->filemime;
        $entity['uid'] = intval($user->uid);
        $entity['public'] = TRUE; // not implemented yet
        $entity['public_dir'] = "/";
        $entity['private_dir'] = "/";
        $entity['updated'] = time();
        $entity = entity_create('filevault', $entity);
        $entity->save();

        $path_id = db_insert('filevault_path')
                      ->fields(array(
                        'id' => NULL,
                        'uid' => $user->uid,
                        'path' => $name,
                        ))
                      ->execute();

        // insert in the tree table with the parent as id.
        $tree_id = db_insert('filevault_tree')
                      ->fields(array(
                        'filevault_path_id' => $parent_id[0]->id,
                        'filevault_files_id' =>  $entity->id,
                        'name' => $newFileName,
                        'type' =>'F',
                        'updated' => REQUEST_TIME,
                        'created' => REQUEST_TIME,
                        ))
                      ->execute();

        // Give the uploader full access
        $access_id = db_insert('filevault_access')
                      ->fields(array(
                        'filevault_path_id' => $path_id,
                        'uid' => $user->uid,
                        'create_access' => 1,
                        'read_access' => 1,
                        'update_access' => 1,
                        'delete_access' => 1,
                        ))
                      ->execute();

        return "Saving success";

    }
  }

  return "Saving error";
}

function filevault_delete_file($path){

  global $user;
  // Do you even have access to delete this path ?

  $path_id =  db_insert('filevault_path')
                ->fields(array(
                    'id' => NULL,
                    'uid' => $user->uid,
                    'path' => $name,
                  ))
                ->execute();






}



function filevault_read_file_object($path){

  global $user;
  $path_id = db_query('SELECT {filevault_path}.id
                       FROM   {filevault_path}
                       WHERE  {filevault_path}.path = :path', array(':path' =>$path))
                       ->fetchAll();

  // Sorry, file not found
  if( count($path_id) == 0 ){
    return "File not found";
  }

  $path_access = db_query('SELECT {filevault_access}.id
                           FROM   {filevault_access}
                           WHERE  {filevault_access}.read_access = 1
                           AND    {filevault_access}.filevault_path_id = :path_id', array(':path_id' =>$path_id))
                           ->fetchAll();

  // Sorry, you don't have access
  if( count($path_access) == 0 ){
    return "Access Denied";
  }

  // load the file
  $path_tree = db_query('  SELECT *
                           FROM  {filevault_tree}
                           WHERE {filevault_tree}.filevault_path_id = :path_id',array(':path_id' =>$path_id))
                           ->fetchAll();

  // load the file
  $file = db_query('  SELECT *
                      FROM  {filevault_tree}
                      WHERE {filevault_tree}.id = :id',array(':id' =>$path_tree->filevault_files_id))
                      ->fetchAll();

  return $file;
}

/**
 * Return a URL to the requested file
 * @param  sting $path
 * @return sting  URL
 */
function filevault_read_file_url($path){

  global $user;
  $path_id = db_query('SELECT {filevault_path}.id
                       FROM   {filevault_path}
                       WHERE  {filevault_path}.path = :path', array(':path' =>$path))
                       ->fetchAll();

  // Sorry, file not found
  if( count($path_id) == 0 ){
    return "File not found";
  }

  $path_access = db_query('SELECT {filevault_access}.id
                           FROM   {filevault_access}
                           WHERE  {filevault_access}.read_access = 1
                           AND    {filevault_access}.filevault_path_id = :path_id', array(':path_id' =>$path_id))
                           ->fetchAll();

  // Sorry, you don't have access
  if( count($path_access) == 0 ){
    return "Access Denied";
  }

  // load the file
  $path_tree = db_query('  SELECT *
                           FROM  {filevault_tree}
                           WHERE {filevault_tree}.filevault_path_id = :path_id',array(':path_id' =>$path_id))
                           ->fetchAll();

  // load the file
  $file = db_query('  SELECT *
                      FROM  {filevault_tree}
                      WHERE {filevault_tree}.id = :id',array(':id' =>$path_tree->filevault_files_id))
                      ->fetchAll();

  return $file;
}

/**
 * filevault_read_file_binary
 *
 * Function to handle sending a file to a WebDAV Client.
 *
 * Warning must not be used in web context as fopen will block others from
 * reading the file, even if fopen, like here, is set to readonly mode. Its a
 * limitation in PHP not the OS.
 *
 * @param  sting      $path   The virtual path of a file
 * @return filehandle         An open file stream to the file
 */
function filevault_read_file_binary($path){

  global $user;
  $path_id = db_query('SELECT {filevault_path}.id
                       FROM   {filevault_path}
                       WHERE  {filevault_path}.path = :path', array(':path' =>$path))
                       ->fetchAll();

  // Sorry, file not found
  if( count($path_id) == 0 ){
    return "File not found";
  }

  $path_access = db_query('SELECT {filevault_access}.id
                           FROM   {filevault_access}
                           WHERE  {filevault_access}.read_access = 1
                           AND    {filevault_access}.filevault_path_id = :path_id', array(':path_id' =>$path_id))
                           ->fetchAll();

  // Sorry, you don't have access
  if( count($path_access) == 0 ){
    return "Access Denied";
  }

  // load the file id
  $path_tree = db_query('  SELECT *
                           FROM  {filevault_tree}
                           WHERE {filevault_tree}.filevault_path_id = :path_id',array(':path_id' =>$path_id))
                           ->fetchAll();

  // load the file
  $file = db_query('  SELECT *
                      FROM  {filevault_tree}
                      WHERE {filevault_tree}.id = :id',array(':id' =>$path_tree->filevault_files_id))
                      ->fetchAll();

  return fopen($file->path,'r');
}


/**
 * Rename andd/or move a file object
 *
 * It will return the path of the object nomatter if the move was successful
 * or not. So the new path if the move was successful
 *
 * @param  string $newPath
 * @param  string $oldPath
 * @return string $path
 */
function filevault_rename($newPath,$oldPath){

  // Do you have write access to the file ?
  global $user;
  $newParent = dirname($newPath);
  $newFileName = basename($newPath);
  $oldParent = dirname($oldPath);
  $oldFileName = basename($oldPath);

  // Get the path id
  $path_id = db_query('SELECT {filevault_path}.id
                       FROM   {filevault_path}
                       WHERE  {filevault_path}.path = :path', array(':path' =>$oldPath))
                       ->fetchAll();

  // Sorry, file not found
  if( count($path_id) == 0 ){
    return "File not found";
  }

  // Do you have write access
  $path_access = db_query('SELECT {filevault_access}.id
                           FROM   {filevault_access}
                           WHERE  {filevault_access}.write_access = 1
                           AND    {filevault_access}.filevault_path_id = :path_id', array(':path_id' =>$path_id))
                           ->fetchAll();

  // Sorry, you don't have access
  if( count($path_access) == 0 ){
    return "Access Denied";
  }

  // Do you have write access to destination ?
  $parent_id = db_query('SELECT {filevault_path}.id
                       FROM   {filevault_path}
                       WHERE  {filevault_path}.path = :path', array(':path' =>$parent))
                       ->fetchAll();

  // Sorry, file not found
  if( count($parent_id) == 0 ){
    return "File not found";
  }

  $path_access = db_query('SELECT {filevault_access}.id
                           FROM   {filevault_access}
                           WHERE  {filevault_access}.write_access = 1
                           AND    {filevault_access}.filevault_path_id = :path_id', array(':path_id' =>$parent_id))
                           ->fetchAll();

  // Sorry, you don't have access
  if( count($path_access) == 0 ){
    return "Access Denied";
  }

  // You have the access required

  // The transaction opens here.
  $txn = db_transaction();

  try {

      $path_id = db_insert('filevault_path')
                    ->fields(array(
                      'id' => NULL,
                      'uid' => $user->uid,
                      'path' => $newFileName,
                      ))
                    ->execute();

      // insert in the tree table with the parent as id.
      $tree_id = db_insert('filevault_tree')
                    ->fields(array(
                      'filevault_path_id' => $parent_id[0]->id,
                      'filevault_files_id' =>  $entity->id,
                      'name' => $newFileName,
                      'type' =>'F',
                      'updated' => REQUEST_TIME,
                      'created' => REQUEST_TIME,
                      ))
                    ->execute();

      // Give the uploader full access
      $access_id = db_insert('filevault_access')
                    ->fields(array(
                      'filevault_path_id' => $path_id,
                      'uid' => $user->uid,
                      'create_access' => 1,
                      'read_access' => 1,
                      'update_access' => 1,
                      'delete_access' => 1,
                      ))
                    ->execute();


    // If the name has change we update the filename, other wise just the
    // updated date.

    if($newFileName ==  $oldFileName  ) {
      $fileUpdate = db_update('filevault_files')
                    ->fields(array(







                    ))
                  ->execute();


      $fileUpdate = db_update('filevault_files')
                    ->fields(array(


                    ))
                    ->execute();
    }


    // Everything went well. Return the new path
    return $newPath;

  }catch(Excention $e){
    // Problem detected. Roolback transaction
    $txn->rollback();

    // Log the exception to watchdog.
    watchdog_exception('type', $e);

    // return the old path
    return $oldPath;
  }

}
