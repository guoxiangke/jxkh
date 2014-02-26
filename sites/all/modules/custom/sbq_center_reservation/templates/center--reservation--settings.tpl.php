<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<table id="center-reservation-table" class="center-reservation">
  <thead>
    <tr>
      <th>星期一</th>
      <th>星期二</th>
      <th>星期三</th>
      <th>星期四</th>
      <th>星期五</th>
      <th>星期六</th>
      <th>星期日</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <?php foreach ($settings as $key=>$s): ?>
        <td>
          <span class="am">
            <input type="checkbox" id="edit-<?php echo $key?>-a" name="<?php echo $key?>[a]" value="a" class="form-checkbox" <?php echo $s['a'] ? 'checked' : '';?>>
            <label class="option" for="edit-<?php echo $key?>-a">上午</label>
          </span>
          <span class="pm">
            <input type="checkbox" id="edit-<?php echo $key?>-p" name="<?php echo $key?>[p]" value="p" class="form-checkbox" <?php  echo $s['p'] ? 'checked' : '';?>>
            <label class="option" for="edit-<?php echo $key?>-p">下午</label>
          </span>
        </td>
      <?php endforeach; ?>
    </tr>
  </tbody>
</table>
