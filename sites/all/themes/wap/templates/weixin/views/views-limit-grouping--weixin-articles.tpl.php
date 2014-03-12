<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php
  $tid = $title;
  $term = taxonomy_term_load($tid);
  $tname = $term->name;
?>
<?php if (!empty($tname)): ?>
  <div class="head"><?php print l($tname, 'wap/weixin/articles/'.$tid.'/all', array('attributes' => array('class' => array('title'))));?></div>
<?php endif; ?>
<ul>
<?php foreach ($rows as $id => $row): ?>
  <?php print $row; ?>
<?php endforeach; ?>
</ul>
