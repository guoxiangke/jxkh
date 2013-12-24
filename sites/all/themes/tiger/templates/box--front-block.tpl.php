<?php
/**
 * @file
 * Default theme implementation for boxes.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) entity label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-{ENTITY_TYPE}
 *   - {ENTITY_TYPE}-{BUNDLE}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<?php
//var_dump($content["field_css_color"]);die;
  $display_title = '';
  $css_classes = '';
  $img = '';
  $link = '';
  $text = '';
  if (isset($content["field_display_title"])) {
    $display_title .= $content["field_display_title"][0]["#markup"];
  }
  if (isset($content["field_css_color"])) {
    $css_classes .= $content["field_css_color"]['#items'][0]["value"];
  }
  if (isset($content["field_css_class"])) {
    $css_classes .= ' '.$content["field_css_class"][0]["#markup"];
  }
  if (isset($content["field_image"])) {
    $img .= render($content["field_image"]);
  }
  if (isset($content["field_link"])) {
    $link .= $content["field_link"][0]["#markup"];
  }
  if (isset($content["field_text"])) {
    $text .= $content["field_text"][0]["#markup"];
  }

?>
<li class="<?php print $css_classes;?>">
  <a href="<?php print $link;?>">
    <div class="sbq_img"><?php print $img;?></div>
    <div class="sbq_title"><?php print $display_title;?></div>
    <div class="sbq_text"><?php print $text;?></div>
  </a>
</li>
