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
/**
 * if question node has been accept a best answer,then no show flag on others answer.
 Ø  提问的患者能够设置最佳答案，且只有一次设置机会
 */
$question_node = node_load(arg(1));
if(isset($question_node->field_mark_question_resolved[LANGUAGE_NONE][0]['value']) && $question_node->field_mark_question_resolved[LANGUAGE_NONE][0]['value'] != 1) {
	 print $output;
	}else {
		$flags = flag_get_counts($entity_type = 'node',$row->nid);
		if(isset($flags['accepted']) && ($flags['accepted'] ==1)) {
			print '<div style="color:red">'.$output.'</div>';	
		}
	}
 
 
// $flag = flag_get_flag($flag_name='accepted');
// $counts = flag_get_entity_flag_counts($flag, );
// dpm(flag_get_counts('node', $row->nid) );
// $flags = flag_get_counts($entity_type = 'node', $row->nid);
?>