<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<div class="componet-<?php echo $display; ?>">
  <ul>
<?php foreach ($components as $k => $v): ?>
      <?php if (strpos($k, 'sbq') !== FALSE): ?>
        <li class="reservation-item <?php echo $k; ?>">
          <span class="item-name"><?php echo $k; ?> </span>>
          <span class="item-value"><?php echo $k ?></span>
        </li>
  <?php endif; ?>
    <?php endforeach; ?>
  </ul>>
</div>
