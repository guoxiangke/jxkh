<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<div id="center-reservation-manage">
  <ul class="ul-item">
    <?php foreach ($header as $k => $v): ?>
      <li class="li-item-header"><?php echo $v; ?></li>
    <?php endforeach; ?>
    <?php if (isset($manage)): ?>
      <li>
        <li class="li-item-header"> 操作</li>
      </li>
    <?php endif; ?>

    <?php foreach ($reservations as $k => $v): ?>
      <ul>
        <?php foreach ($v as $key => $value): ?>
          <li class="li-item <?php echo $key; ?>"> 
            <span class="span-name-<?php echo $key; ?>"><?php echo $value['#title'] ?></span>
            <?php if ($key == 'sbq_center_file'): ?>
              <span class="span-value-<?php echo $key; ?>"><img src="<?php echo $value['#value'] ?>"></span>
            <?php else: ?>
              <span class="span-value-<?php echo $key; ?>"><?php echo $value['#value'] ?></span>
            <?php endif; ?>

          </li>
        <?php endforeach; ?>
        <?php if (isset($manage)): ?>
          <li>
            <?php echo l('接受', 'node/' . $nid . '/reservation/' . $k . '/action/accept') ?>
            <?php echo l('忽略', 'node/' . $nid . '/reservation/' . $k . '/action/ignore') ?>
          </li>
        <?php endif; ?>
      </ul>
    <?php endforeach; ?>
  </ul>
</div>