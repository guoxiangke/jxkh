<?php
/**
 * Implements hook_views_default_views().
 */
function druedu_qa_views_default_views() {
	//view questions
	{
	$view = new view();
	$view->name = 'questions';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Questions';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Questions & Answers';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['query']['options']['distinct'] = TRUE;
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '5';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['pager']['options']['id'] = '0';
	$handler->display->display_options['pager']['options']['quantity'] = '9';
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['style_options']['row_class'] = 'clearfix';
	$handler->display->display_options['row_plugin'] = 'fields';
	$handler->display->display_options['row_options']['default_field_elements'] = FALSE;
	/* Relationship: Content: Author */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'node';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	$handler->display->display_options['relationships']['uid']['required'] = TRUE;
	/* Relationship: Content: Votes */
	$handler->display->display_options['relationships']['votingapi_vote']['id'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['table'] = 'node';
	$handler->display->display_options['relationships']['votingapi_vote']['field'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['votingapi'] = array(
	  'value_type' => 'points',
	  'tag' => 'vote',
	);
	$handler->display->display_options['relationships']['votingapi_vote']['current_user'] = 0;
	/* Field: Votes: Value */
	$handler->display->display_options['fields']['value']['id'] = 'value';
	$handler->display->display_options['fields']['value']['table'] = 'votingapi_vote';
	$handler->display->display_options['fields']['value']['field'] = 'value';
	$handler->display->display_options['fields']['value']['relationship'] = 'votingapi_vote';
	$handler->display->display_options['fields']['value']['label'] = '';
	$handler->display->display_options['fields']['value']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['value']['alter']['text'] = '<span class="number">[value]</span><span class="vote">Votes</span>';
	$handler->display->display_options['fields']['value']['element_label_type'] = 'div';
	$handler->display->display_options['fields']['value']['element_label_class'] = 'vote-question';
	$handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['value']['precision'] = '0';
	/* Field: Content: computed_answers */
	$handler->display->display_options['fields']['field_computed_answers']['id'] = 'field_computed_answers';
	$handler->display->display_options['fields']['field_computed_answers']['table'] = 'field_data_field_computed_answers';
	$handler->display->display_options['fields']['field_computed_answers']['field'] = 'field_computed_answers';
	$handler->display->display_options['fields']['field_computed_answers']['label'] = '';
	$handler->display->display_options['fields']['field_computed_answers']['alter']['text'] = '<span>[field_computed_answers-value]</span><span>Answers</span>';
	$handler->display->display_options['fields']['field_computed_answers']['element_label_colon'] = FALSE;
	/* Field: Content statistics: Total views */
	$handler->display->display_options['fields']['totalcount']['id'] = 'totalcount';
	$handler->display->display_options['fields']['totalcount']['table'] = 'node_counter';
	$handler->display->display_options['fields']['totalcount']['field'] = 'totalcount';
	$handler->display->display_options['fields']['totalcount']['label'] = '';
	$handler->display->display_options['fields']['totalcount']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['totalcount']['alter']['text'] = '<span>[totalcount]</span><span>Views</span>';
	$handler->display->display_options['fields']['totalcount']['element_label_colon'] = FALSE;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	/* Field: Content: Body */
	$handler->display->display_options['fields']['body']['id'] = 'body';
	$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
	$handler->display->display_options['fields']['body']['field'] = 'body';
	$handler->display->display_options['fields']['body']['label'] = '';
	$handler->display->display_options['fields']['body']['alter']['max_length'] = '600';
	$handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
	$handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
	$handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
	$handler->display->display_options['fields']['body']['settings'] = array(
	  'trim_length' => '600',
	);
	/* Field: Content: Tags */
	$handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
	$handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
	$handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
	$handler->display->display_options['fields']['field_tags']['label'] = '';
	$handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
	/* Field: User: Picture */
	$handler->display->display_options['fields']['picture']['id'] = 'picture';
	$handler->display->display_options['fields']['picture']['table'] = 'users';
	$handler->display->display_options['fields']['picture']['field'] = 'picture';
	$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
	$handler->display->display_options['fields']['picture']['label'] = '';
	$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['picture']['image_style'] = 'profile_small';
	/* Field: Node: Published at */
	$handler->display->display_options['fields']['published_at']['id'] = 'published_at';
	$handler->display->display_options['fields']['published_at']['table'] = 'publication_date';
	$handler->display->display_options['fields']['published_at']['field'] = 'published_at';
	$handler->display->display_options['fields']['published_at']['label'] = '';
	$handler->display->display_options['fields']['published_at']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['published_at']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['published_at']['date_format'] = 'sbq_date_medium_revert';
	$handler->display->display_options['fields']['published_at']['custom_date_format'] = '1';
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = '';
	$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
	/* Field: Content: Edit link */
	$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['label'] = '';
	$handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
	/* Field: Content: Delete link */
	$handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['label'] = '';
	$handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	/* Sort criterion: Content: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['sorts']['created']['order'] = 'DESC';
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'question' => 'question',
	);

	/* Display: Question List */
	$handler = $view->new_display('page', 'Question List', 'page_questions_list');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Questions';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['arguments'] = FALSE;
	/* Contextual filter: Global: Null */
	$handler->display->display_options['arguments']['null']['id'] = 'null';
	$handler->display->display_options['arguments']['null']['table'] = 'views';
	$handler->display->display_options['arguments']['null']['field'] = 'null';
	$handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
	$handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
	$handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
	$handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
	$handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
	$handler->display->display_options['arguments']['null']['validate']['type'] = 'php';
	$handler->display->display_options['arguments']['null']['validate_options']['code'] = 'if (empty($argument)) {
	  return TRUE;
	} else {
	  return FALSE;
	}';
	$handler->display->display_options['arguments']['null']['validate']['fail'] = 'empty';
	$handler->display->display_options['path'] = 'questions';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'Question';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'menu-q-a-menu';
	$handler->display->display_options['menu']['context'] = 0;

	/* Display: My Questions */
	$handler = $view->new_display('page', 'My Questions', 'page_my_questions');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'My Questions';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['relationships'] = FALSE;
	/* Relationship: Content: Author */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'node';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	$handler->display->display_options['relationships']['uid']['required'] = TRUE;
	/* Relationship: Content: Votes */
	$handler->display->display_options['relationships']['votingapi_vote']['id'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['table'] = 'node';
	$handler->display->display_options['relationships']['votingapi_vote']['field'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['votingapi'] = array(
	  'value_type' => 'points',
	  'tag' => 'vote',
	);
	$handler->display->display_options['relationships']['votingapi_vote']['current_user'] = 0;
	$handler->display->display_options['defaults']['arguments'] = FALSE;
	$handler->display->display_options['defaults']['filter_groups'] = FALSE;
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'question' => 'question',
	);
	/* Filter criterion: User: Current */
	$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
	$handler->display->display_options['filters']['uid_current']['table'] = 'users';
	$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
	$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
	$handler->display->display_options['filters']['uid_current']['value'] = '1';
	$handler->display->display_options['path'] = 'questions/my-questions';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'My Questions';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'menu-q-a-menu';
	$handler->display->display_options['menu']['context'] = 0;

	/* Display: Unanswered Questions */
	$handler = $view->new_display('page', 'Unanswered Questions', 'page_unanswered_questions');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Unanswered Questions';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['relationships'] = FALSE;
	/* Relationship: Content: Author */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'node';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	$handler->display->display_options['relationships']['uid']['required'] = TRUE;
	/* Relationship: Content: Votes */
	$handler->display->display_options['relationships']['votingapi_vote']['id'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['table'] = 'node';
	$handler->display->display_options['relationships']['votingapi_vote']['field'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['votingapi'] = array(
	  'value_type' => 'points',
	  'tag' => 'vote',
	);
	$handler->display->display_options['relationships']['votingapi_vote']['current_user'] = 0;
	/* Relationship: Flags: accepted */
	$handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
	$handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
	$handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
	$handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
	$handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'accepted';
	$handler->display->display_options['defaults']['arguments'] = FALSE;
	$handler->display->display_options['defaults']['filter_groups'] = FALSE;
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'question' => 'question',
	);
	/* Filter criterion: Content: Mark Question Resolved (field_mark_question_resolved) */
	$handler->display->display_options['filters']['field_mark_question_resolved_value']['id'] = 'field_mark_question_resolved_value';
	$handler->display->display_options['filters']['field_mark_question_resolved_value']['table'] = 'field_data_field_mark_question_resolved';
	$handler->display->display_options['filters']['field_mark_question_resolved_value']['field'] = 'field_mark_question_resolved_value';
	$handler->display->display_options['filters']['field_mark_question_resolved_value']['value'] = array(
	  0 => '0',
	);
	$handler->display->display_options['path'] = 'questions/unanswered';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'Unanswered Questions';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'menu-q-a-menu';
	$handler->display->display_options['menu']['context'] = 0;

	/* Display: CountAllQuestion */
	$handler = $view->new_display('block', 'CountAllQuestion', 'block_counts_all_question');
	$handler->display->display_options['display_description'] = 'Counts of All Questions';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['group_by'] = FALSE;
	$handler->display->display_options['group_by'] = TRUE;
	$handler->display->display_options['defaults']['query'] = FALSE;
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['query']['options']['distinct'] = TRUE;
	$handler->display->display_options['defaults']['relationships'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['group_type'] = 'count';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	$handler->display->display_options['defaults']['sorts'] = FALSE;

	/* Display: Tagged */
	$handler = $view->new_display('page', 'Tagged', 'page_questions_tagged');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Questions';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Votes: Value */
	$handler->display->display_options['fields']['value']['id'] = 'value';
	$handler->display->display_options['fields']['value']['table'] = 'votingapi_vote';
	$handler->display->display_options['fields']['value']['field'] = 'value';
	$handler->display->display_options['fields']['value']['relationship'] = 'votingapi_vote';
	$handler->display->display_options['fields']['value']['label'] = '';
	$handler->display->display_options['fields']['value']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['value']['alter']['text'] = '<span class="number">[value]</span><span class="vote">Votes</span>';
	$handler->display->display_options['fields']['value']['element_label_type'] = 'div';
	$handler->display->display_options['fields']['value']['element_label_class'] = 'vote-question';
	$handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['value']['precision'] = '0';
	/* Field: Content: computed_answers */
	$handler->display->display_options['fields']['field_computed_answers']['id'] = 'field_computed_answers';
	$handler->display->display_options['fields']['field_computed_answers']['table'] = 'field_data_field_computed_answers';
	$handler->display->display_options['fields']['field_computed_answers']['field'] = 'field_computed_answers';
	$handler->display->display_options['fields']['field_computed_answers']['label'] = '';
	$handler->display->display_options['fields']['field_computed_answers']['alter']['text'] = '<span>[field_computed_answers-value]</span><span>Answers</span>';
	$handler->display->display_options['fields']['field_computed_answers']['element_label_colon'] = FALSE;
	/* Field: Content statistics: Total views */
	$handler->display->display_options['fields']['totalcount']['id'] = 'totalcount';
	$handler->display->display_options['fields']['totalcount']['table'] = 'node_counter';
	$handler->display->display_options['fields']['totalcount']['field'] = 'totalcount';
	$handler->display->display_options['fields']['totalcount']['label'] = '';
	$handler->display->display_options['fields']['totalcount']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['totalcount']['alter']['text'] = '<span>[totalcount]</span><span>Views</span>';
	$handler->display->display_options['fields']['totalcount']['element_label_colon'] = FALSE;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	/* Field: Content: Body */
	$handler->display->display_options['fields']['body']['id'] = 'body';
	$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
	$handler->display->display_options['fields']['body']['field'] = 'body';
	$handler->display->display_options['fields']['body']['label'] = '';
	$handler->display->display_options['fields']['body']['alter']['max_length'] = '600';
	$handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
	$handler->display->display_options['fields']['body']['alter']['html'] = TRUE;
	$handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
	$handler->display->display_options['fields']['body']['settings'] = array(
	  'trim_length' => '600',
	);
	/* Field: Content: Tags */
	$handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
	$handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
	$handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
	$handler->display->display_options['fields']['field_tags']['label'] = '';
	$handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
	/* Field: User: Picture */
	$handler->display->display_options['fields']['picture']['id'] = 'picture';
	$handler->display->display_options['fields']['picture']['table'] = 'users';
	$handler->display->display_options['fields']['picture']['field'] = 'picture';
	$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
	$handler->display->display_options['fields']['picture']['label'] = '';
	$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['picture']['image_style'] = 'profile_small';
	/* Field: Node: Published at */
	$handler->display->display_options['fields']['published_at']['id'] = 'published_at';
	$handler->display->display_options['fields']['published_at']['table'] = 'publication_date';
	$handler->display->display_options['fields']['published_at']['field'] = 'published_at';
	$handler->display->display_options['fields']['published_at']['label'] = '';
	$handler->display->display_options['fields']['published_at']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['published_at']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['published_at']['date_format'] = 'q_a_date';
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = '';
	$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
	/* Field: Content: Edit link */
	$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['label'] = '';
	$handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
	/* Field: Content: Delete link */
	$handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['label'] = '';
	$handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	$handler->display->display_options['defaults']['filter_groups'] = FALSE;
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'question' => 'question',
	);
	/* Filter criterion: Content: Tags (field_tags) */
	$handler->display->display_options['filters']['field_tags_tid']['id'] = 'field_tags_tid';
	$handler->display->display_options['filters']['field_tags_tid']['table'] = 'field_data_field_tags';
	$handler->display->display_options['filters']['field_tags_tid']['field'] = 'field_tags_tid';
	$handler->display->display_options['filters']['field_tags_tid']['value'] = '';
	$handler->display->display_options['filters']['field_tags_tid']['exposed'] = TRUE;
	$handler->display->display_options['filters']['field_tags_tid']['expose']['operator_id'] = 'field_tags_tid_op';
	$handler->display->display_options['filters']['field_tags_tid']['expose']['label'] = 'Tagged';
	$handler->display->display_options['filters']['field_tags_tid']['expose']['operator'] = 'field_tags_tid_op';
	$handler->display->display_options['filters']['field_tags_tid']['expose']['identifier'] = 'field_tags_tid';
	$handler->display->display_options['filters']['field_tags_tid']['expose']['remember_roles'] = array(
	  2 => '2',
	  1 => 0,
	  3 => 0,
	  4 => 0,
	  5 => 0,
	  6 => 0,
	);
	$handler->display->display_options['filters']['field_tags_tid']['vocabulary'] = 'tags';
	$handler->display->display_options['path'] = 'questions/tagged';
	$handler->display->display_options['menu']['title'] = 'Question';
	$handler->display->display_options['menu']['weight'] = '0';
	$handler->display->display_options['menu']['name'] = 'menu-q-a-menu';
	$handler->display->display_options['menu']['context'] = 0;
}
	//end 
	$views[$view->name] = $view;
	//single page begin
{	
	$view = new view();
	$view->name = 'question';
	$view->description = 'A view to show one single question one page.';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Single question';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'questions';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '1';
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['style_options']['row_class'] = 'clearfix';
	$handler->display->display_options['row_plugin'] = 'fields';
	$handler->display->display_options['row_options']['default_field_elements'] = FALSE;
	/* Relationship: Content: Author */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'node';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	/* Relationship: Content: Votes */
	$handler->display->display_options['relationships']['votingapi_vote']['id'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['table'] = 'node';
	$handler->display->display_options['relationships']['votingapi_vote']['field'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote']['votingapi'] = array(
	  'value_type' => 'points',
	  'tag' => 'vote',
	);
	$handler->display->display_options['relationships']['votingapi_vote']['current_user'] = 0;
	/* Relationship: Content: Votes */
	$handler->display->display_options['relationships']['votingapi_vote_1']['id'] = 'votingapi_vote_1';
	$handler->display->display_options['relationships']['votingapi_vote_1']['table'] = 'node';
	$handler->display->display_options['relationships']['votingapi_vote_1']['field'] = 'votingapi_vote';
	$handler->display->display_options['relationships']['votingapi_vote_1']['label'] = 'Votes Options is useful';
	$handler->display->display_options['relationships']['votingapi_vote_1']['votingapi'] = array(
	  'value_type' => 'option',
	  'tag' => 'vote',
	);
	$handler->display->display_options['relationships']['votingapi_vote_1']['current_user'] = 0;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['title']['element_type'] = 'h2';
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
	/* Field: Votes: Value */
	$handler->display->display_options['fields']['value']['id'] = 'value';
	$handler->display->display_options['fields']['value']['table'] = 'votingapi_vote';
	$handler->display->display_options['fields']['value']['field'] = 'value';
	$handler->display->display_options['fields']['value']['relationship'] = 'votingapi_vote';
	$handler->display->display_options['fields']['value']['label'] = '';
	$handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['value']['precision'] = '0';
	$handler->display->display_options['fields']['value']['appearance'] = 'rate_views_widget';
	/* Field: Content: Body */
	$handler->display->display_options['fields']['body']['id'] = 'body';
	$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
	$handler->display->display_options['fields']['body']['field'] = 'body';
	$handler->display->display_options['fields']['body']['label'] = '';
	$handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
	/* Field: Content: Tags */
	$handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
	$handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
	$handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
	$handler->display->display_options['fields']['field_tags']['label'] = '';
	$handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
	/* Field: User: Picture */
	$handler->display->display_options['fields']['picture']['id'] = 'picture';
	$handler->display->display_options['fields']['picture']['table'] = 'users';
	$handler->display->display_options['fields']['picture']['field'] = 'picture';
	$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
	$handler->display->display_options['fields']['picture']['label'] = '';
	$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['picture']['image_style'] = 'profile_small';
	/* Field: Content: Post date */
	$handler->display->display_options['fields']['created']['id'] = 'created';
	$handler->display->display_options['fields']['created']['table'] = 'node';
	$handler->display->display_options['fields']['created']['field'] = 'created';
	$handler->display->display_options['fields']['created']['label'] = '';
	$handler->display->display_options['fields']['created']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['created']['alter']['text'] = '[created]';
	$handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['created']['date_format'] = 'sbq_date_medium_revert';
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = '';
	$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
	/* Field: Content: Edit link */
	$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['label'] = '';
	$handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
	/* Field: Content: Delete link */
	$handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['label'] = '';
	$handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
	/* Field: Votes: Value */
	$handler->display->display_options['fields']['value_1']['id'] = 'value_1';
	$handler->display->display_options['fields']['value_1']['table'] = 'votingapi_vote';
	$handler->display->display_options['fields']['value_1']['field'] = 'value';
	$handler->display->display_options['fields']['value_1']['relationship'] = 'votingapi_vote_1';
	$handler->display->display_options['fields']['value_1']['label'] = '';
	$handler->display->display_options['fields']['value_1']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['value_1']['precision'] = '0';
	$handler->display->display_options['fields']['value_1']['appearance'] = 'rate_views_widget';
	/* Field: Field: Attachments */
	$handler->display->display_options['fields']['field_attachments']['id'] = 'field_attachments';
	$handler->display->display_options['fields']['field_attachments']['table'] = 'field_data_field_attachments';
	$handler->display->display_options['fields']['field_attachments']['field'] = 'field_attachments';
	$handler->display->display_options['fields']['field_attachments']['label'] = '';
	$handler->display->display_options['fields']['field_attachments']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_attachments']['click_sort_column'] = 'filevault_id';
	$handler->display->display_options['fields']['field_attachments']['type'] = 'filevault_field_formatter_link';
	$handler->display->display_options['fields']['field_attachments']['delta_offset'] = '0';
	$handler->display->display_options['fields']['field_attachments']['separator'] = '<br> ';
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	/* Field: Content revision: Nid */
	$handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
	$handler->display->display_options['fields']['nid_1']['table'] = 'node_revision';
	$handler->display->display_options['fields']['nid_1']['field'] = 'nid';
	$handler->display->display_options['fields']['nid_1']['label'] = '';
	$handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['nid_1']['alter']['text'] = 'remove';
	$handler->display->display_options['fields']['nid_1']['alter']['make_link'] = TRUE;
	$handler->display->display_options['fields']['nid_1']['alter']['path'] = 'node/[nid]/remove';
	$handler->display->display_options['fields']['nid_1']['alter']['alt'] = 'remove';
	$handler->display->display_options['fields']['nid_1']['alter']['link_class'] = 'use-ajax btn btn-link btn-delete-node ajax-processed';
	$handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
	/* Sort criterion: Content: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['sorts']['created']['order'] = 'DESC';
	/* Contextual filter: Content: Nid */
	$handler->display->display_options['arguments']['nid']['id'] = 'nid';
	$handler->display->display_options['arguments']['nid']['table'] = 'node';
	$handler->display->display_options['arguments']['nid']['field'] = 'nid';
	$handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
	$handler->display->display_options['arguments']['nid']['title_enable'] = TRUE;
	$handler->display->display_options['arguments']['nid']['title'] = '%1';
	$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
	$handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
	$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
	$handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
	$handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
	$handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
	$handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
	  'question' => 'question',
	);
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'question' => 'question',
	);

	/* Display: single question page */
	$handler = $view->new_display('page', 'single question page', 'single_question_page');
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['path'] = 'questions/%';

	/* Display: answers attachment */
	$handler = $view->new_display('attachment', 'answers attachment', 'answers_attachment');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'answers';
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
	$handler->display->display_options['pager']['type'] = 'none';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['defaults']['relationships'] = FALSE;
	/* Relationship: Entity Reference: Referenced Entity */
	$handler->display->display_options['relationships']['field_answer_target_id']['id'] = 'field_answer_target_id';
	$handler->display->display_options['relationships']['field_answer_target_id']['table'] = 'field_data_field_answer';
	$handler->display->display_options['relationships']['field_answer_target_id']['field'] = 'field_answer_target_id';
	$handler->display->display_options['relationships']['field_answer_target_id']['required'] = TRUE;
	/* Relationship: Content: Vote results */
	$handler->display->display_options['relationships']['votingapi_cache']['id'] = 'votingapi_cache';
	$handler->display->display_options['relationships']['votingapi_cache']['table'] = 'node';
	$handler->display->display_options['relationships']['votingapi_cache']['field'] = 'votingapi_cache';
	$handler->display->display_options['relationships']['votingapi_cache']['votingapi'] = array(
	  'value_type' => 'points',
	  'tag' => 'vote',
	  'function' => 'sum',
	);
	/* Relationship: Content: Author */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'node';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	/* Relationship: Content: Vote results */
	$handler->display->display_options['relationships']['votingapi_cache_1']['id'] = 'votingapi_cache_1';
	$handler->display->display_options['relationships']['votingapi_cache_1']['table'] = 'node';
	$handler->display->display_options['relationships']['votingapi_cache_1']['field'] = 'votingapi_cache';
	$handler->display->display_options['relationships']['votingapi_cache_1']['label'] = 'Vote option is useful';
	$handler->display->display_options['relationships']['votingapi_cache_1']['votingapi'] = array(
	  'value_type' => 'option',
	  'tag' => '',
	  'function' => '',
	);
	/* Relationship: Flags: accepted */
	$handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
	$handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
	$handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
	$handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
	$handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'accepted';
	$handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Vote results: Value */
	$handler->display->display_options['fields']['value']['id'] = 'value';
	$handler->display->display_options['fields']['value']['table'] = 'votingapi_cache';
	$handler->display->display_options['fields']['value']['field'] = 'value';
	$handler->display->display_options['fields']['value']['relationship'] = 'votingapi_cache';
	$handler->display->display_options['fields']['value']['label'] = '';
	$handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['value']['precision'] = '0';
	$handler->display->display_options['fields']['value']['appearance'] = 'rate_views_widget';
	/* Field: Content: Body */
	$handler->display->display_options['fields']['body']['id'] = 'body';
	$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
	$handler->display->display_options['fields']['body']['field'] = 'body';
	$handler->display->display_options['fields']['body']['label'] = '';
	$handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
	/* Field: User: Picture */
	$handler->display->display_options['fields']['picture']['id'] = 'picture';
	$handler->display->display_options['fields']['picture']['table'] = 'users';
	$handler->display->display_options['fields']['picture']['field'] = 'picture';
	$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
	$handler->display->display_options['fields']['picture']['label'] = '';
	$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['picture']['image_style'] = 'comment_avatar';
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = '';
	$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
	/* Field: Content: Post date */
	$handler->display->display_options['fields']['created']['id'] = 'created';
	$handler->display->display_options['fields']['created']['table'] = 'node';
	$handler->display->display_options['fields']['created']['field'] = 'created';
	$handler->display->display_options['fields']['created']['label'] = '';
	$handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['created']['date_format'] = 'sbq_date_medium_revert';
	$handler->display->display_options['fields']['created']['custom_date_format'] = '1';
	/* Field: Vote results: Value */
	$handler->display->display_options['fields']['value_1']['id'] = 'value_1';
	$handler->display->display_options['fields']['value_1']['table'] = 'votingapi_cache';
	$handler->display->display_options['fields']['value_1']['field'] = 'value';
	$handler->display->display_options['fields']['value_1']['relationship'] = 'votingapi_cache_1';
	$handler->display->display_options['fields']['value_1']['label'] = '';
	$handler->display->display_options['fields']['value_1']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['value_1']['precision'] = '0';
	$handler->display->display_options['fields']['value_1']['appearance'] = 'rate_views_widget';
	/* Field: Content: Edit link */
	$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['label'] = '';
	$handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
	/* Field: Content: Delete link */
	$handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['label'] = '';
	$handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
	/* Field: Flags: Flag link */
	$handler->display->display_options['fields']['ops']['id'] = 'ops';
	$handler->display->display_options['fields']['ops']['table'] = 'flag_content';
	$handler->display->display_options['fields']['ops']['field'] = 'ops';
	$handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
	$handler->display->display_options['fields']['ops']['label'] = '';
	$handler->display->display_options['fields']['ops']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['ops']['element_default_classes'] = FALSE;
	$handler->display->display_options['fields']['ops']['link_type'] = 'toggle';
	/* Field: Field: Attachments */
	$handler->display->display_options['fields']['field_attachments']['id'] = 'field_attachments';
	$handler->display->display_options['fields']['field_attachments']['table'] = 'field_data_field_attachments';
	$handler->display->display_options['fields']['field_attachments']['field'] = 'field_attachments';
	$handler->display->display_options['fields']['field_attachments']['label'] = '';
	$handler->display->display_options['fields']['field_attachments']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_attachments']['click_sort_column'] = 'filevault_id';
	$handler->display->display_options['fields']['field_attachments']['type'] = 'filevault_field_formatter_link';
	$handler->display->display_options['fields']['field_attachments']['delta_offset'] = '0';
	$handler->display->display_options['fields']['field_attachments']['separator'] = ' , ';
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	/* Field: Content revision: Nid */
	$handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
	$handler->display->display_options['fields']['nid_1']['table'] = 'node_revision';
	$handler->display->display_options['fields']['nid_1']['field'] = 'nid';
	$handler->display->display_options['fields']['nid_1']['label'] = '';
	$handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['nid_1']['alter']['text'] = 'remove';
	$handler->display->display_options['fields']['nid_1']['alter']['make_link'] = TRUE;
	$handler->display->display_options['fields']['nid_1']['alter']['path'] = 'node/[nid]/remove';
	$handler->display->display_options['fields']['nid_1']['alter']['alt'] = 'remove';
	$handler->display->display_options['fields']['nid_1']['alter']['link_class'] = 'use-ajax btn btn-link btn-delete-node ajax-processed';
	$handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
	$handler->display->display_options['defaults']['sorts'] = FALSE;
	/* Sort criterion: Flags: Flagged time */
	$handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
	$handler->display->display_options['sorts']['timestamp']['table'] = 'flag_content';
	$handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
	$handler->display->display_options['sorts']['timestamp']['relationship'] = 'flag_content_rel';
	$handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
	/* Sort criterion: Vote results: Value */
	$handler->display->display_options['sorts']['value']['id'] = 'value';
	$handler->display->display_options['sorts']['value']['table'] = 'votingapi_cache';
	$handler->display->display_options['sorts']['value']['field'] = 'value';
	$handler->display->display_options['sorts']['value']['relationship'] = 'votingapi_cache';
	$handler->display->display_options['sorts']['value']['order'] = 'DESC';
	$handler->display->display_options['sorts']['value']['coalesce'] = 1;
	/* Sort criterion: Content: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['defaults']['arguments'] = FALSE;
	/* Contextual filter: Content: Nid */
	$handler->display->display_options['arguments']['nid']['id'] = 'nid';
	$handler->display->display_options['arguments']['nid']['table'] = 'node';
	$handler->display->display_options['arguments']['nid']['field'] = 'nid';
	$handler->display->display_options['arguments']['nid']['relationship'] = 'field_answer_target_id';
	$handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
	$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
	$handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
	$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
	$handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
	$handler->display->display_options['defaults']['filter_groups'] = FALSE;
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
	  'answer' => 'answer',
	);
	$handler->display->display_options['displays'] = array(
	  'single_question_page' => 'single_question_page',
	  'default' => 0,
	);
	$handler->display->display_options['attachment_position'] = 'after';
}
	//single page end.
	$views[$view->name] = $view;

	//question tags block begin
{
	$view = new view();
	$view->name = 'questions_tags';
	$view->description = 'Questions tags  or  tags of Q&A related';
	$view->tag = 'default';
	$view->base_table = 'taxonomy_term_data';
	$view->human_name = 'Questions tags';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Popular Tags';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['group_by'] = TRUE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '5';
	$handler->display->display_options['style_plugin'] = 'default';
	$handler->display->display_options['row_plugin'] = 'fields';
	$handler->display->display_options['row_options']['default_field_elements'] = FALSE;
	/* Relationship: Taxonomy term: Content using Tags */
	$handler->display->display_options['relationships']['reverse_field_tags_node']['id'] = 'reverse_field_tags_node';
	$handler->display->display_options['relationships']['reverse_field_tags_node']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['relationships']['reverse_field_tags_node']['field'] = 'reverse_field_tags_node';
	$handler->display->display_options['relationships']['reverse_field_tags_node']['required'] = TRUE;
	/* Field: Taxonomy term: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['label'] = '';
	$handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
	$handler->display->display_options['fields']['name']['alter']['path'] = 'questions/tagged?field_tags_tid=[name]';
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
	/* Field: COUNT(Taxonomy term: Name) */
	$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
	$handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['fields']['name_1']['field'] = 'name';
	$handler->display->display_options['fields']['name_1']['group_type'] = 'count';
	$handler->display->display_options['fields']['name_1']['label'] = '';
	$handler->display->display_options['fields']['name_1']['element_type'] = 'span';
	$handler->display->display_options['fields']['name_1']['element_class'] = 'tags_num';
	$handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['name_1']['element_default_classes'] = FALSE;
	/* Sort criterion: COUNT(Taxonomy term: Term ID) */
	$handler->display->display_options['sorts']['tid']['id'] = 'tid';
	$handler->display->display_options['sorts']['tid']['table'] = 'taxonomy_term_data';
	$handler->display->display_options['sorts']['tid']['field'] = 'tid';
	$handler->display->display_options['sorts']['tid']['group_type'] = 'count';
	$handler->display->display_options['sorts']['tid']['order'] = 'DESC';
	/* Filter criterion: Taxonomy vocabulary: Machine name */
	$handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
	$handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
	$handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
	$handler->display->display_options['filters']['machine_name']['value'] = array(
	  'tags' => 'tags',
	);

	/* Display: Block */
	$handler = $view->new_display('block', 'Block', 'block');
	$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
}
	//question tags block end 
	$views[$view->name] = $view;
	//end 
	return $views;
}