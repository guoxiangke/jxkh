<?php
/**
 * @file
 * Template to display a row
 * 
 * - $inner: The rendered string of the row's contents.
 */
$attrs = ($class) ? 'class="' . $class . '"' : '';
$attrs .= ($iehint > 0) ? ' iehint="' . $iehint . '"' : '';
?>
<?php if (arg(0) == 'center'):  //for center?>
  <?php if ($class != 'single-day'): ?>
    <?php if ($attrs != ''): ?>
      <tr <?php print $attrs ?>>
      <?php else: ?>
      <tr>
      <?php endif; ?>
      <?php print $inner ?>
    </tr>
  <?php endif; ?>
<?php else : ?>
  <?php if ($attrs != ''): ?>
    <tr <?php print $attrs ?>>
    <?php else: ?>
    <tr>
    <?php endif; ?>
    <?php print $inner ?>
  </tr>

<?php endif; ?>
