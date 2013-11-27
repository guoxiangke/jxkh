<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
$bedges = array(
    't1' => array(
        'picture' => 't1.png',
        'name' => '模范家属',
        'info' => '模范家属'
    ),
    't2' => array(
        'picture' => 't2.png',
        'name' => '悬壶济世',
        'info' => '悬壶济世'
    ),
    't3' => array(
        'picture' => 't3.png',
        'name' => '勇敢超人',
        'info' => '勇敢超人'
    ),
    't4' => array(
        'picture' => 't4.png',
        'name' => '爱心大使',
        'info' => '2013.10.30日。伤不起组织敬老院活动，招募5人，报名10人。全网共10枚。'
    ),
);
?>

<div class="sbq-bedges">
  <?php
  foreach ($bedges as $k => $v):
    ?>
    <div class="bedges">
      <div  class="picture">
        <img src="<?php echo drupal_get_path('module', 'sbq_commons') . '/images/' . $v['picture']; ?>">
      </div>
      <div class="info">
        <span> 介绍:</span> <?php echo $v['info']; ?>
      </div>
    </div>
  <?php endforeach; ?>
</div>