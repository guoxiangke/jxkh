<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<div class="sbq-user-relationship-profile">
  <div class="image">
    <?php echo $image ?>
  </div>
  <div class="info">
    <?php foreach ($profile as $key => $item): ?>
      <?php if (!empty($item)): ?>
        <span class="<?php echo $key; ?>">
          <?php echo $item ?>
        </span> 
      <?php endif; ?>
    <?php endforeach; ?>
  </div>
</div>
