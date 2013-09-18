<label><?php print t('Attachment files'); ?></label>
<div id="ui_upload">
  <div id="dragndrop-area" class="admin">
    <p class="dragndrop"> <?php print t("Drag'n'drop to upload files or"); ?></p>
    <span class="pc_files">
      <a class="btn"> <?php print t('Upload new files'); ?></a>
    </span>
    <span class="server_files">
      <button class="btn" data-target="#filevault-modal" role="button" data-toggle="modal" id="big-media"><?php print t('Files on server'); ?></button>
    </span>
  </div>
  <section id="filevault_ui_block" class="hide block">
    <div class="progress_bars">
      <div class="progress" id="progress_all">
        <div class="bar" style="width: 0%;"></div>
      </div>
    </div>
  </section>
</div>
<div id="files_uploaded" class="hide">
  <h4><?php print t('Files uploaded'); ?></h4>
  <div id="files_uploaded_container">
      <?php print $files; ?>
   </div>
</div>