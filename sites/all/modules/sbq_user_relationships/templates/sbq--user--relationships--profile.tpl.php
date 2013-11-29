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
    <?php
    $name = $profile['name'];
    unset($profile['name']);

    $bedges = $profile['bedges'];
    unset($profile['bedges']);
    ?>
    <div class="warp-nb">
      <span class="name">
       <?php echo $name ?>
      </span> 
       <span class="bedges">
       <?php echo $bedges; ?>
      </span> 
    </div>
    <?php foreach ($profile as $key => $item): ?>
        <?php if (!empty($item)): ?>
        <span class="<?php echo $key; ?>">
        <?php echo $item ?>
        </span> 
  <?php endif; ?>
<?php endforeach; ?>
  </div>
</div>
<?php ?>