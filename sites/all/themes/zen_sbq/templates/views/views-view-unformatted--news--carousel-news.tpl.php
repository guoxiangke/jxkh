<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php foreach ($rows as $id => $row): ?>
  <div class="carousel-inner">
      <div<?php
  if ($classes_array[$id]) {
    print ' class="' . $classes_array[$id] . ' item active"';
  }
  ?>>
          <?php print $row; ?>
      </div>
  </div>
<?php endforeach; ?>