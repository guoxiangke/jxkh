<?php
/**
 * @file
 * druedu_qa_features.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function druedu_qa_features_default_rules_configuration() {
  $items = array();
  $items['rules_mark_question_resolved'] = entity_import('rules_config', '{ "rules_mark_question_resolved" : {
      "LABEL" : "Mark Question Resolved",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "qanda" ],
      "REQUIRES" : [ "druedu_qa", "flag" ],
      "ON" : [ "flag_flagged_accepted" ],
      "DO" : [
        { "druedu_qa_action_unflag_the_old_answer" : { "new_answer" : [ "flagged-node" ] } },
        { "druedu_qa_action_mark_question_resolved" : { "new_answer" : [ "flagged-node" ] } }
      ]
    }
  }');
  $items['rules_mark_question_unresolved'] = entity_import('rules_config', '{ "rules_mark_question_unresolved" : {
      "LABEL" : "Mark Question UnResolved",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "qanda" ],
      "REQUIRES" : [ "druedu_qa", "flag" ],
      "ON" : [ "flag_unflagged_accepted" ],
      "DO" : [
        { "druedu_qa_action_mark_question_unresolved" : { "unflagged_answer" : [ "flagged-node" ] } }
      ]
    }
  }');
  return $items;
}
