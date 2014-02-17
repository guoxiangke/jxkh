<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <div class="sbq_head"><?php print $title; ?></div>
<?php endif; ?>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tbody>
    <tr>
      <th width="120">预约号</th>
      <th width="100">患者姓名</th>
      <th width="120">联系电话</th>
      <th width="120">就诊时间</th>
      <th width="100">预约状态</th>
    </tr>
    <?php foreach ($rows as $id => $row): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
  </tbody>
</table>
