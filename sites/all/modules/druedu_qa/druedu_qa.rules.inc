<?php

/**
 * @file Includes any rules integration provided by the module.
 */
 /**
 * implementation of hook_rules_condition_info()
 */
function druedu_qa_rules_condition_info() {
  return array(
    'druedu_qa_condition_has_the_best_answer' => array(
      'label' => t('If there is an old best answer for the question already.'),
      'arguments' => array(
        'new_answer' => array('type' => 'node', 'label' => t('The new answer node.')),
      ),
      'module' => 'druedu_qa',
      'group' => t('Customs'),
    ),
  );
}
/**
 * Condition druedu_qa_condition_has_the_best_answer
 */
function druedu_qa_condition_has_the_best_answer($new_answer) {
  
  $question_nid = $new_answer->field_answer[LANGUAGE_NONE]['0']['target_id'];
  $question = node_load($question_nid);
  $answers_array = $question->field_answers[LANGUAGE_NONE];
  $flag_name = 'accepted';// oh..oh,the name must match system flag setting in /admin/structure/flags
  if (!($flag = flag_get_flag($flag_name))) {
      // Flag does not exist.
      return FALSE;
  }
  foreach ($answers_array as $key => $value) {
    $nid = $value['target_id'];
    // flag_flag->is_flagged($content_id, $uid = NULL, $sid = NULL)
    if($flag->is_flagged($nid) && $nid!=$new_answer->nid){
      return TRUE;
    }
  }
  return FALSE;
}

 /**
 * implementation of hook_rules_condition_info()
 */
function druedu_qa_rules_action_info() {
  return array(
    'druedu_qa_action_unflag_the_old_answer' => array(
      'label' => t('1.Unflag the old answer from given new answer,if has.'),
      'arguments' => array(
        'new_answer' => array('type' => 'node', 'label' => t('The new answer someone gives.')),
      ),
      'module' => 'druedu_qa',
      'group' => t('Customs'),
    ),
    'druedu_qa_action_mark_question_resolved' => array(
      'label' => t('2.mark a question is resolved while an answer flaged accepet.'),
      'arguments' => array(
        'new_answer' => array('type' => 'node', 'label' => t('The answer flagged accept.')),
      ),
      'module' => 'druedu_qa',
      'group' => t('Customs'),
    ),
    // an accepted answer unflagged && not attepted another one.
    'druedu_qa_action_mark_question_unresolved' => array(
      'label' => t('3.mark a question has no resolved while an accepeted answer unflaged .'),
      'arguments' => array(
        'unflagged_answer' => array('type' => 'node', 'label' => t('The answer unflagged accepted.')),
      ),
      'module' => 'druedu_qa',
      'group' => t('Customs'),
    ),
    //
    'druedu_qa_action_new_answer' => array(
      'label' => t('Add the answer to the question\'s Entity Reference field when a new answer was created.'),
      'arguments' => array(
        'answer' => array('type' => 'node', 'label' => t('The answer someone gives.')),
      ),
      'module' => 'druedu_qa',
      'group' => t('Customs'),
    ),
  );
}
/**
 * Condition packages_condition_packagetype
 */
function druedu_qa_action_unflag_the_old_answer($new_answer) {
   //Provide the the old answer as parameter to unflag?
   //do something, no return.

  $question_nid = $new_answer->field_answer[LANGUAGE_NONE]['0']['target_id'];
  $question = node_load($question_nid);
  $answers_array = $question->field_answers[LANGUAGE_NONE];
  $flag_name = 'accepted';// here also,the name must match system flag setting in /admin/structure/flags
  if (!($flag = flag_get_flag($flag_name))) {
      // Flag does not exist.
      return;
  }
  foreach ($answers_array as $key => $value) {
    $nid = $value['target_id'];
    if($flag->is_flagged($nid) && $nid!=$new_answer->nid){
      flag('unflag',$flag_name,$nid);
      return;
    }
  }
  return;
}
 /**
 * Condition druedu_qa_action_mark_question_resolved
 * $question_node:field_answer-->$question_node:field_mark_question_resolved
 */
function druedu_qa_action_mark_question_resolved($answer_node) {
  $node = node_load($answer_node->field_answer[LANGUAGE_NONE]['0']['target_id']);//$question_node 
  //if(!$node->field_mark_question_resolved[LANGUAGE_NONE]['0']['value']){
    //watchdog('$type', $node->nid.':'.$answer_node->nid.'-'.$node->field_mark_question_resolved[LANGUAGE_NONE]['0']['value']);
    $node->field_mark_question_resolved[LANGUAGE_NONE]['0']['value']=1;
    node_save($node);
    //watchdog('$type2', $node->nid.':'.$answer_node->nid.'-'.$node->field_mark_question_resolved[LANGUAGE_NONE]['0']['value']);
  //}
  return;
}

 /**
 * Condition druedu_qa_action_mark_question_unresolved
 * $question_node:field_answer-->$question_node:field_answers(All)-->none of is flagged.
 */
function druedu_qa_action_mark_question_unresolved($answer_node) {
  //$question_node 
  $node = node_load($answer_node->field_answer[LANGUAGE_NONE]['0']['target_id']);
  //if($node->field_mark_question_resolved[LANGUAGE_NONE]['0']['value']){//must be 1(booleans true)
    $node->field_mark_question_resolved[LANGUAGE_NONE]['0']['value']=0;
    node_save($node);
  //}
  return;
}



/**
 *  Add a new reference field value to the question when a new answer was created for it. 
 */
function druedu_qa_action_new_answer($answer) {
  $question_nid = $answer->field_answer[LANGUAGE_NONE]['0']['target_id'];
  $question = node_load($question_nid);
  $question->field_answers[LANGUAGE_NONE][]=array('target_id'=>$answer->nid);
  node_save($question);
}