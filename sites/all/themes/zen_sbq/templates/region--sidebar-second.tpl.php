<?php
/**
 * @file
 * Returns HTML for a sidebar region.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728118
 */
?>
<?php if ($content): ?>
  <section class="<?php print $classes; ?> col-md-4">
  <div class="sidebar_warpper">
    <?php print $content; ?>
   </div>
  </section>
<?php endif; ?>
