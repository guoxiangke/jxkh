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
$is_reservation = sbq_center_reservation_can_reservation($item['date'], '', TRUE);
$display_item = $item['class'] != 'single-day no-entry future' && $item['class'] != 'single-day no-entry past' && $item['class'] != 'single-day no-entry today';
?>

  <td <?php print $id ?>class="<?php print $item['class'] ?>" colspan="<?php print $item['colspan'] ?>" rowspan="<?php print $item['rowspan'] ?>"<?php print $date . $headers . $day; ?>>
    <?php if ($is_reservation): ?>
      <a href="/center/<?php echo arg(1); ?>/reservation/created?date=<?php echo $item['date']?>">
        <div class="inner reservation-item"  style="background: red;">
          <?php
          print $item['entry'];
          ?>
        </div>
      </a>
    <?php else : ?>
      <div class="inner">
        <?php print $item['entry'] ?>
      </div>
    <?php endif; ?>
  </td>
