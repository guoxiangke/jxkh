<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>

<?php
$title = $field->original_value;
//$path = $field->options['alter']['path'];
//@see http://projects.crystal-asia.com/projects/bcis-education-groupware/tasks/291
$path = 'node/'.$row->nid.'/delete/nojs';
?>
<?php print l($title, $path, array('attributes' => array('class' => array('use-ajax', 'btn', 'btn-link', 'btn-delete-node')))); ?>
