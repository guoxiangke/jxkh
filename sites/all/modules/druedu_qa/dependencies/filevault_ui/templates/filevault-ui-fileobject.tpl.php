<?php

/**
 *  File Object Template
 *
 *  This template will render a fileobejct. It has a diffrent sections for each
 *  file type.
 *
 *  Variables for all types:
 *
 *  $type           // Contains the type of object. Type is based on mime type
 *  $display        // For now "icon" and "preview", can be expaned later
 *  $original       // URL to the original file
 *  $label          // The name of the file object
 *  $size           // The name of the file
 *  $icon           // URL for the icon
 *  $path           // path
 *
 *  // Images
 *  $thumbnail      // The thumbnail size
 *  $embedded       // The embedeed size
 *
 *  // Video
 *  $poster         // URL to the poster image
 *
 *  // Audio
 *  $poster         // URL to the poster image
 *
 *  // Document
 *  $poster         // URL to the poster image
 *
 */
?>

<div class="fileobject <?php print $type; ?> <?php print $displaytype; ?>">
  <img src="/<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/delete.png" height="32" width="32" alt="delete" class="fw_delete" data-fw_path="<?php print $path ?>"/>

  <?php
  /**
   * Image files
   *
   */
  ?>
  <?php if ($type == "image"): ?>

    <?php if ($display == "icon"): ?>
      <a href="<?php print $original ?>">
        <img src="<?php print $thumbnail; ?>" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

    <?php if ($display == "preview"): ?>
      <a href="<?php print $original ?>">
        <img src="<?php print $embedded; ?>" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

  <?php endif; ?>

  <?php
  /**
   * Video files
   *
   */
  ?>
  <?php if ($type == "video"): ?>

    <?php if ($display == "icon"): ?>
      <video id="example_video_1" class="video-js vjs-default-skin" controls width="128" height="96" poster="/<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/video_128.png" preload="metadata" data-setup="{}">
        <source type="video/mp4" src="<?php print $original; ?>">
      </video>
    <?php endif; ?>

    <?php if ($display == "preview"): ?>
      <video id="example_video_1" class="video-js vjs-default-skin" controls width="512" height="384" poster="/<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/video_512.png" preload="metadata" data-setup="{}">
        <source type="video/mp4" src="<?php print $original; ?>">
      </video>
    <?php endif; ?>

  <?php endif; ?>

  <?php
  /**
   * Audio files
   *
   */
  ?>
  <?php if ($type == "audio"): ?>

    <?php if ($display == "icon"): ?>
      <a href="<?php print $original ?>">
        <img src="<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/file_128.png" height="128" width="128" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

    <?php if ($display == "preview"): ?>
      <a href="<?php print $original ?>">
        <img src="<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/file_512.png" height="512" width="512" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

  <?php endif; ?>

  <?php
  /**
   * Directory
   *
   */
  ?>
  <?php if ($type == "directory"): ?>

    <?php if ($display == "icon"): ?>
      <a href="/<?php print request_path()."/".$label; ?>">
        <img src="/<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/folder_128.png" height="128" width="128" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

    <?php if ($display == "preview"): ?>
      <a href="<?php print $original ?>">
        <img src="/<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/folder_512.png" height="512" width="512" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

  <?php endif; ?>

  <?php
  /**
   * Documents and other files not respresented above. The default option
   *
   */
  ?>
  <?php if ($type == "document"): ?>

    <?php if ($display == "icon"): ?>
      <a href="<?php print $original ?>">
        <img src="/<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/file_128.png" height="128" width="128" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

    <?php if ($display == "preview"): ?>
      <a href="<?php print $original ?>">
        <img src="/<?php print drupal_get_path('module', 'filevault_ui'); ?>/img/file_512.png" height="512" width="512" alt="<?php print $label; ?>" />
      </a>
    <?php endif; ?>

  <?php endif; ?>

  <div class="filename"><?php print $label; ?></div>
</div>
