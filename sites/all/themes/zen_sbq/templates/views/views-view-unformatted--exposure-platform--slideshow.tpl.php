<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
	<? if($id==0) {
		echo '<div class="item active">';
	}elseif($id==3 || $id==6) {// 
		echo '<div class="item">';
	}?>
  <div <?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; //echo "rows-$id";//?>

  </div>
  	<? if($id==2 || $id==5 || $id==8) {
		echo '</div>';
	}?>
<?php endforeach; ?>