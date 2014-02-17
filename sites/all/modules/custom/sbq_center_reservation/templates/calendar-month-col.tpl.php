<?php
/**
 * @file
 * Template to display a column
 *
 * - $item: The item to render within a td element.
 */
$id = (isset($item['id'])) ? 'id="' . $item['id'] . '" ' : '';
$date = (isset($item['date'])) ? ' data-date="' . $item['date'] . '" ' : '';
$day = (isset($item['day_of_month'])) ? ' data-day-of-month="' . $item['day_of_month'] . '" ' : '';
$headers = (isset($item['header_id'])) ? ' headers="' . $item['header_id'] . '" ' : '';
if (arg(0) == 'center') {
  $is_reservation = sbq_center_reservation_can_reservation($item['date'], '', 'day');
  $display_item = $item['class'] != 'single-day no-entry future' && $item['class'] != 'single-day no-entry past' && $item['class'] != 'single-day no-entry today';
}
?>

<td <?php print $id ?>class="<?php print $item['class'] ?>" colspan="<?php print $item['colspan'] ?>" rowspan="<?php print $item['rowspan'] ?>"<?php print $date . $headers . $day; ?>>
  <?php if(arg(0) == 'center') : ?>
  <div class="inner reservation-item">
    <?php if ($is_reservation): ?>
      <div class="month day">
        <?php
        print $item['entry'];
        ?>
      </div>
      <div class="inner">
        <div class="sbq_order_actions">
          <dl>
            <dt>上午</dt>
            <dd>
              <?php if ($is_reservation['am']): ?>
                <a href="/center/<?php echo arg(1); ?>/reservation/created?date=<?php echo $item['date'] ?> 10:00" class="sbq_add">预约</a>
              <?php else: ?>
                <a href="#" class="sbq_full">约满</a>
              <?php endif; ?>
            </dd>
          </dl>
          <dl>
            <dt>下午</dt>
            <dd>
              <?php if ($is_reservation['am']): ?>
                <a href="/center/<?php echo arg(1); ?>/reservation/created?date=<?php echo $item['date'] ?> 14:00" class="sbq_add">预约</a>
              <?php else: ?>
                <a href="#" class="sbq_full">约满</a>
              <?php endif; ?>
            </dd>
          </dl>
        </div>
      </div>
    <?php else: ?>
      <?php
      print $item['entry'];
      ?>
    <?php endif; ?>
  </div>
  <?php else: ?>
  <div class="inner">
    <?php print $item['entry'] ?>
  </div>
  <?php endif; ?>
</td>




