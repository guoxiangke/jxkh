<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php kpr($title); ?>
<?php if (!empty($title)): ?>
  <div class="sbq_news_list_head"><?php print $title; ?></div>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <?php print $row; ?>
<?php endforeach; ?>
