<?php

/**
 *  Filevault page Template
 *
 *  This template will render the filevault page.
 *
 *  Variables:
 *
 *  $fileobejcts           // Contains the type of object. Type is based on mime type
 *
 */

/*
                <?php foreach ($fileObejcts as $delta => $file) : ?>
                <?php print render($fileObejcts); ?>
                <?php endforeach; ?>
 */
?>

<div class="container-fluid">

        <!-- Top toolbar -->
        <div class="row-fluid">
          <div class="span6 offset2">
                <div class="btn-group" data-toggle="buttons-checkbox">
                    <button type="button" class="btn"><i class="icon-camera"></i> Photos</button>
                    <button type="button" class="btn"><i class="icon-film"></i> Movies</button>
                    <button type="button" class="btn"><i class="icon-headphones"></i> Audio</button>
                    <button type="button" class="btn"><i class="icon-file"></i> Documents</button>
                </div>
            </div>
            <div class="span4">
                <form class="form-search pull-right">
                    <input type="text" class="input-medium search-query">
                    <button type="submit" class="btn">Search</button>
                </form>
            </div>
        </div>

        <!-- Sidebar -->
        <div class="row-fluid">
            <div class="span2">
                <div class="fileinfo">
                	<form>
                      <fieldset>
                        <legend>File info</legend>
                        <label>Label name</label>
                        <input type="text" placeholder="Type something…">
                        <span class="help-block">Example block-level help text here.</span>
                        <label class="checkbox">
                          <input type="checkbox"> Public
                        </label>
                        
                        <div class="input-append">
  							<input class="span2" placeholder="Username…" id="appendedInputButton" type="text">
  							<button class="btn" type="button">Share</button>
						</div>
                        
                        
                        <button type="submit" class="btn">Save</button>
                      </fieldset>
                    </form>
                </div>
            </div>

            <!-- Main content -->
            <div class="span10">

                <?php if (!$filesfound): ?>
                    <div class="nofilesfound">
                        <h2>No files or directories found in this directory</h2>
                    </div>
                <?php endif; ?>

                <?php if ($filesfound): ?>
                    <ul class="fw_filelist">
                        <?php foreach ($fileobjects as $file) : ?>
                            <li class="fw_file">
                                <?php print theme('filevault_ui_fileobject', array('fileobject' => $file, 'display' => 'icon', 'path'=> $path)); ?>
                            </li>
                        <?php endforeach; ?>
                    </ul>
                <?php endif; ?>
            </div>
        </div>

</div>

