<?php

/**
 *  Note: Later many of the db calls can be replaced with stored procedures.
 *  This will make the filevault much much faster
 */

/**
 * Returns a access object for the current user
 *
 * @param  string $path
 * @return array crud
 */
function filevault_get_crud($path){

  global $user;

  // Admin always have access
  if( $user->uid == 1 ){
    return array('create' => 1, 'read' => 1, 'update' => 1, 'delete' => 1 );
  }

  $path_id = db_query('SELECT {filevault_path}.id
                       FROM {filevault_path}
                       WHERE path = :path', array(':path' =>$path))
                       ->fetchAll();

  // The path does not exist, so it must be a new file object
  // Then do we have access to write in this directory ?
  if( count($path_id) == 0 ){
    $newDir = basename($path);
    $parent = dirname($path);

    $path_id = db_query(' SELECT {filevault_path}.id
                          FROM {filevault_path}
                          WHERE path = :path', array(':path' =>$parent))
                          ->fetchAll();

    // The wanted path and it's parent can't be found. Something is fishy
    // Return noaccess rights
    if( count($path_id) == 0 ){
      return array('create' => 0, 'read' => 0, 'update' => 0, 'delete' => 0 );
    }
  }

  // We got a path let's find the access rights for the current user
  $path_access = db_query('SELECT *
                           FROM   {filevault_access}
                           WHERE  {filevault_access}.uid = :uid
                           AND    {filevault_access}.filevault_path_id = :path_id', array(':path_id' =>$path_id[0]->id,':uid' =>$user->uid))
                           ->fetchAll();

  // The path exsist but there is no access rights set for the current path
  // so return noaccess rights
  if( count($path_access) == 0 ){
    return array('create' => 0, 'read' => 0, 'update' => 0, 'delete' => 0 );
  }

  // We got a crud object! Nice, let's return it
  return array('create' => $path_access[0]->create_access,
               'read'   => $path_access[0]->read_access,
               'update' => $path_access[0]->update_access,
               'delete' => $path_access[0]->delete_access );

}

/**
 * Set the access rights to a specific user
 *
 * @param  int    $uid  User ID
 * @param  array  $crud List of access rights
 * @param  string $path path as a sting
 * @return boolean      success or not
 */
function filevault_set_crud($uid, $crud, $path){

  // get the path id
  $path_id = db_query('SELECT {filevault_path}.id
                       FROM {filevault_path}
                       WHERE path = :path', array(':path' =>$path))
                       ->fetchAll();

  // Did we get an id ?
  if( count($path_id) == 0 ){
    // path not found
    return false;
  }

  // Give the uploader full access
  $access_id = db_insert('filevault_access')
                      ->fields(array(
                        'filevault_path_id' => $path_id,
                        'uid' => $uid,
                        'create_access' => $crud['create'],
                        'read_access'   => $crud['read'],
                        'update_access' => $crud['update'],
                        'delete_access' => $crud['delete'],
                        ))
                      ->execute();
  // Yay !
  return true;
}

/**
 * Check path if it exists
 *
 * @param  string   $path The path we wish to check
 * @return boolean        Does it exists or not
 */
function filevault_path_exists($path){

  $path_id = db_query('SELECT {filevault_path}.id
                       FROM {filevault_path}
                       WHERE path = :path', array(':path' =>$path))
                       ->fetchAll();

  // Sorry, there is a file object with that name
  if( count($path_id) == 0 ){
    return false;
  }

  // No fileobejct with that name
  return $path_id;
}

/**
 * Create a new directory
 *
 * @param  string  $path The new path
 * @return boolean       success or not
 */
function filevault_create_directory($path){

  global $user;

  // Get the access rights for the current directory
  $crud = filevault_get_crud(dirname($path));

  // Do you have access
  if(!$crud['create']){
    // Sorry
    return false;
  }

  // Okay you have access. Is there a file or directory with this name
  // in the directory already?
  if(filevault_path_exists($path)){
    // Sorry
    return false;
  }

  // Does the parent exites
  $parent_id = filevault_path_exists(dirname($path));
  if( count($parent_id) == 0 ){
    // Cound not find the parent
    return false;
  }

  // Everything is cool, let's create that directory

  // insert the new path in the path table
  $path_id    =   db_insert('filevault_path')
                      ->fields(array(
                        'id' => NULL,
                        'uid' => $user->uid,
                        'path' => $path,
                        ))
                      ->execute();

  // insert it the tree table with the parent as id.
  $tree_id    =   db_insert('filevault_tree')
                      ->fields(array(
                        'filevault_path_id' => $parent_id[0]->id,
                        'name' => basename($path),
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

  return true;
}



/**
 *  Create a new file
 *
 * @param  string $name The full name of a file ex: /home/john/movie.mp4
 * @param  binary $data binary data or file handle
 * @return boolean      success or not
 */
function filevault_create_file($path, $data){

  global $user;

  // Get the access rights for the current user
  $crud = filevault_get_crud(dirname($path));

  // Do you have access
  if(!$crud['create']){
    // Sorry
    return false;
  }

  // Okay you have access. Is there a file or directory with this name
  // in the directory already?
  if(filevault_path_exists($path)){
    // Sorry
    return false;
  }

  // Does the parent exites
  $parent_id = filevault_path_exists(dirname($path));
  if( count($parent_id) == 0 ){
    // Cound not find the parent
    return false;
  }

  error_log("parent_id:".print_r($parent_id,true)."\n", 3, "/Users/jens/www/debugentity/drupal-7.15/sites/all/modules/filevault_webdav/webdav.log");

  error_log("parent_id:".print_r(dirname($path),true)."\n", 3, "/Users/jens/www/debugentity/drupal-7.15/sites/all/modules/filevault_webdav/webdav.log");

  // Everything is cool, let's create that file
  $file = file_save_data($data,'temporary://'.basename($path));

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

        // Insert the new path
        $path_id = db_insert('filevault_path')
                      ->fields(array(
                        'id' => NULL,
                        'uid' => $user->uid,
                        'path' => $path,
                        ))
                      ->execute();

        // insert in the tree table with the parent as id.
        $tree_id = db_insert('filevault_tree')
                      ->fields(array(
                        'filevault_path_id' => $parent_id[0]->id,
                        'filevault_files_id' => $entity->id,
                        'name' => $file->filename,
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

      error_log("File Created\n", 3, "/Users/jens/www/debugentity/drupal-7.15/sites/all/modules/filevault_webdav/webdav.log");

        return true;
    }
  }

  return false;
}

/**
 * Deletes a file in the vault
 *
 * @param  sting  $path The full name of a file ex: /home/john/movie.mp4
 * @return boolean      success or not
 */
function filevault_delete_file($path){

  // Get the access rights for the current user
  $crud = filevault_get_crud($path);

  // Do you have access
  if(!$crud['delete']){
    // Sorry
    return false;
  }

  // Does it exists
  $path_id = filevault_path_exists($path);
  if(!$path_id){
    // Sorry
    return false;
  }

  // Find the ID of the file
  $filevault_files_id = db_query('SELECT {filevault_tree}.filevault_files_id
                                  FROM {filevault_tree}
                                  WHERE {filevault_tree}.filevault_path_id = :path_id',array(':path_id' =>$path_id))
                                  ->fetchAll();

  // Delete the file from the tree
  $num_deleted = db_delete('filevault_tree')
                 ->condition('filevault_path_id', $path_id[0]->id)
                 ->execute();

  // Delete the files access rights
  $num_deleted = db_delete('filevault_access')
                 ->condition('filevault_path_id', $path_id[0]->id)
                 ->execute();

  // Delete the file from files table
  $num_deleted = db_delete('filevault_files')
                 ->condition('id', $filevault_files_id[0]->filevault_files_id)
                 ->execute();

  // Delete the file from path table
  $num_deleted = db_delete('filevault_path')
                 ->condition('id', $path_id[0]->id)
                 ->execute();

  // We are good
  return true;
}



/**
 * Return a file as a filevault object
 *
 * @param  string $path The full name of a file ex: /home/john/movie.mp4
 * @return object       The fully load object, null, if not found
 */
function filevault_read_file_object($path){

  // Get the access rights for the current user
  $crud = filevault_get_crud($path);

  // Do you have access
  if(!$crud['read']){
    // Sorry
    return null;
  }

  // Does it exists
  $path_id = filevault_path_exists($path);
  if(!$path_id){
    // Sorry
    return null;
  }

  // Does the parent exites
  $parent_id = filevault_path_exists(dirname($path));
  if( count($parent_id) == 0 ){
    // Cound not find the parent
    return false;
  }



  // Find it in the tree
  $path_tree = db_query('SELECT *
                         FROM  {filevault_tree}
                         WHERE {filevault_tree}.filevault_path_id = :path_id
                         AND  {filevault_tree}.name = :name',
                         array(':path_id' =>$parent_id[0]->id,':name' => basename($path)))
                         ->fetchAll();

  // Load the file
  $file = db_query('SELECT *
                    FROM  {filevault_files}
                    WHERE {filevault_files}.id = :id', array(':id' =>$path_tree[0]->filevault_files_id))
                    ->fetchAll();

  error_log("File object return:".$file[0]->filename."\n", 3, "/Users/jens/www/debugentity/drupal-7.15/sites/all/modules/filevault_webdav/webdav.log");

  // Return the file object
  return $file;
}

/**
 * Return a URL to the requested file
 * @param  string $path The full name of a file ex: /home/john/movie.mp4
 * @return string       URL
 */
function filevault_read_file_url($path){

  // Get the access rights for the current user
  $crud = filevault_get_crud($path);

  // Do you have access
  if(!$crud['delete']){
    // Sorry
    return false;
  }

  // Does it exists
  $path_id = filevault_path_exists($path);
  if(!$path_id){
    // Sorry
    return false;
  }

  // load the file in the tree
  $path_tree = db_query('SELECT *
                         FROM  {filevault_tree}
                         WHERE {filevault_tree}.filevault_path_id = :path_id',array(':path_id' =>$path_id[0]->id))
                         ->fetchAll();

  // load the file
  $file = db_query('SELECT *
                    FROM  {filevault_tree}
                    WHERE {filevault_tree}.id = :id',array(':id' =>$path_tree[0]->filevault_files_id))
                    ->fetchAll();

  return $file;
}

/**
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

  // Get the access rights for the current user
  $crud = filevault_get_crud($path);

  // Do you have access
  if(!$crud['delete']){
    // Sorry
    return false;
  }

  // Does it exists
  $path_id = filevault_path_exists($path);
  if(!$path_id){
    // Sorry
    return false;
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

  // Does it exists
  $path_id = filevault_path_exists($oldPath);

  // Sorry, file not found
  if( count($path_id) == 0 ){
    return "File not found";
  }

  // Get the access rights for the current user
  $crud = filevault_get_crud($oldPath);
  // Do you have access
  if(!$crud['update']){
    // Sorry
    return false;
  }

  // Does the parent exites
  $parent_id = filevault_path_exists(dirname($newPath));
  if( count($parent_id) == 0 ){
    // Cound not find the parent
    return false;
  }

  // Same directory
  if(dirname($newPath) == dirname($oldPath)){
    // Get the access rights for the current user
    $crud = filevault_get_crud(dirname($newPath));
    // Do you have access
    if(!$crud['update']){
      // Sorry
      return false;
    }
  }

  // diff directory
  if(dirname($newPath) != dirname($oldPath)){
    // Get the access rights for the current user
    $crud = filevault_get_crud(dirname($newPath));
    // Do you have access
    if(!$crud['create']){
      // Sorry
      return false;
    }
  }
  error_log("filevault_rename access granted\n", 3, "/Users/jens/www/debugentity/drupal-7.15/sites/all/modules/filevault_webdav/webdav.log");

  // You have the access required

  // The transaction opens here.
  $txn = db_transaction();

  try {

      // Change the name in the lookup table
      $num_updated = db_update('filevault_path')
                      ->fields(array(
                                      'path' => $newPath,
                                    ))
                      ->condition('id', $path_id[0]->id, '=')
                      ->execute();

      // Did we do an update ?
      if($num_updated == 0){
         throw new Exception('DB error: Trying to rename: "'.$oldPath.'" to "'.$newPath.'" in the tabel filevault_path. The current path was not found.');
      }

      // Change the update time and name in the tree
      $num_updated = db_update('filevault_tree')
                      ->fields(array(
                                      'name' => basename($newPath),
                                      'updated' => REQUEST_TIME,
                                    ))
                      ->condition('filevault_path_id', $parent_id[0]->id, '=')
                      ->condition('name', basename($oldPath), '=')
                      ->execute();

      // Did we do an update
      if($num_updated == 0){
         throw new Exception('DB error: Trying to rename: "'.$oldPath.'" to "'.$newPath.'" in the tabel filevault_tree. The current path was not found.');
      }

      //Update the paths of child elements in the path lookup table
      $sql = 'SELECT * FROM {filevault_path} WHERE path LIKE :pattern';
      $result = db_query($sql, array(':pattern' => db_like($oldPath).'%'));
      $paths = $result->fetchAll();

      foreach ($paths as $path_record) {

        if (substr($path_record->path, 0, strlen($oldPath)) == $oldPath) {
          $tail = substr($path_record->path, strlen($oldPath), strlen($path_record->path) );
        }

        $path_record->path = $newPath.$tail;

        $num_updated = db_update('filevault_path')
                        ->fields(array(
                                      'path' => $path_record->path,
                                      ))
                        ->condition('id', $path_record->id, '=')
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

/**
 * Get a list of fileobject from a specific path
 *
 * @param  string $path The full name of a file ex: /home/john/movie.mp4
 * @return array        The file obejcts in a given path
 */
function filevault_list_files($path){

  // Get the access rights for the current user
  $crud = filevault_get_crud($path);

  // Do you have access
  if(!$crud['read']){
    // Sorry
    return array();
  }

  // Does it exists
  $path_id = filevault_path_exists($path);
  if(!$path_id){
    // Sorry
    return array();
  }

  // Find the content in the Directory
  $dirsAndFiles = db_query('SELECT *
                            FROM {filevault_tree}
                            WHERE filevault_path_id = :id',array(':id' => $path_id[0]->id ))
                            ->fetchAll();

  // Return the list of file objects
  return $dirsAndFiles;

}

/**
 * Delete a directory
 *
 * @param  string $path The full name of a file ex: /home/john/movie.mp4
 * @return boolean      success or not
 */
function filevault_delete_directory($path){

  // Get the access rights for the current user
  $crud = filevault_get_crud($path);

  // Do you have access
  if(!$crud['delete']){
    // Sorry
    return false;
  }

  // Does it exists
  $path_id = filevault_path_exists($path);
  if(!$path_id){
    // Sorry
    return false;
  }

  // Delete the file from the tree
  $num_deleted = db_delete('filevault_tree')
                 ->condition('filevault_path_id', $path_id[0]->id)
                 ->execute();

  // Delete the files access rights
  $num_deleted = db_delete('filevault_access')
                 ->condition('filevault_path_id', $path_id[0]->id)
                 ->execute();

  // Delete the file from path table
  $num_deleted = db_delete('filevault_path')
                 ->condition('id', $path_id[0]->id)
                 ->execute();

  return true;

}

