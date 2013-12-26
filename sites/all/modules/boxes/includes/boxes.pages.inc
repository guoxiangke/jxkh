<?php

/**
 * @file
 * Box Functions
 */

/**
 * Edit box page callback
 */
function boxes_edit(Box $box) {
  $type = boxes_fetch_plugin_info($box->type);
  drupal_set_title(t('<em>Edit @type</em> @title', array('@type' => $type['label'], '@title' => $box->label)), PASS_THROUGH);
  return drupal_get_form('boxes_form', $box);
}

/**
 * Add box page callback
 */
function boxes_add($type) {
  $box = boxes_create(array('type' => $type));
  $box_type = boxes_type_load($type);
  drupal_set_title(t('Create @type block', array('@type' => $box_type->getLabel())), PASS_THROUGH);

  return drupal_get_form('boxes_form', $box, $type);
}

/**
 * Menu Callback to list available box types to add
 */
function boxes_add_page() {
  $box_types = boxes_get_types();
  // Bypass the block/add listing if only one block type is available.
  if (count($box_types) == 1) {
    $box_type = array_shift($box_types);
    drupal_goto('block/add/' . $box_type->buildURL());
  }

  return theme('boxes_add_list', array('content' => $box_types));
}

/**
 * Render a listing of all Boxes.
 */
function boxes_list() {
  $rows = array();

  // Build the sortable table header.
  $header = array(
    'title' => array(
      'data' => 'Title',
      'type' => 'property',
      'specifier' => 'title',
      'sort' => 'asc'
    ),
    'type' => array(
      'data' => 'Type',
      'type' => 'entity',
      'specifier' => 'bundle',
    ),
    'operations' => array('data' => t('Operations')),
  );

  $filters = boxes_get_filter();


  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'box')
    ->tableSort($header)
    ->pager($filters['per_page']);

  if (!empty($filters['types'])) {
    $query->entityCondition('bundle', $filters['types'], 'IN');
  }

  $result = $query->execute();
  if (!empty($result)) {
    $boxes = boxes_load_multiple(array_keys($result['box']));
  }
  else {
    $boxes = array();
  }

  foreach ($boxes as $box) {
    $rows[$box->bid] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $box->label,
          '#href' => 'block/' . $box->delta,
        ),
      ),
      'type' => check_plain($box->type),
    );

    $destination = drupal_get_destination();

    // Build a list of all the accessible operations for the current box.
    $operations = array();
    $operations['edit'] = array(
      'title' => t('edit'),
      'href' => 'block/' . $box->delta . '/edit',
      'query' => $destination,
    );
    $operations['delete'] = array(
      'title' => t('delete'),
      'href' => 'block/' . $box->delta . '/delete',
      'query' => $destination,
    );
    // Render an unordered list of operations links.
    $rows[$box->bid]['operations'] = array(
      'data' => array(
        '#theme' => 'links__boxes_operations',
        '#links' => $operations,
        '#attributes' => array('class' => array('links', 'inline')),
      ),
    );
  }

  $output = array(
    'boxes_filter_form' => drupal_get_form('boxes_filter_form'),
    'boxes_content' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('There are no Block Available'),
    ),
    'pager' => array(
      '#theme' => 'pager',
    ),
  );

  return $output;
}

/**
 * Returns HTML for a list of available box types for box creation.
 *
 * @param $variables
 *   An associative array containing:
 *   - content: An array of box types.
 *
 * @ingroup themeable
 */
function theme_boxes_add_list($variables) {
  $content = $variables['content'];
  $blocks = array();
  $i = 0;

  if ($content) {
    foreach ($content as $item) {
      $title = l(t('<span class="icon"></span>@label', array('@label' => $item->getLabel())), 'block/add/' . $item->buildURL(), array('html' => TRUE));
      $description = (!is_array($item->getDescription())) ? '<div class="description">' . $item->getDescription() . '</div>' : '';
      //creative way to setup sorting by label; add number to prevent duplicate keys
      $blocks[str_replace(' ', '', $item->getLabel()) . '_' . $i] = '<li>' . $title . $description . '</li>';
      $i++;
    }
    ksort($blocks);
    $output = '<ul class="box-type-list admin-list">' . implode('', $blocks) . '</ul>';
  }
  else {
    $output = '<p>' . t('You have not created any block types yet.') . '</p>';
  }
  return $output;
}

/**
 * Boxes form
 */
function boxes_form($form, &$form_state, Box $box, $type = NULL) {

  // During initial form build, add the box entity to the form state for use
  // during form building and processing. During a rebuild, use what is in the
  // form state.
  if (!isset($form_state['box'])) {
    if (!isset($box->label)) {
      $box->label = NULL;
    }
    if (isset($type)) {
      $box->type = $type;
    }
    $form_state['box'] = $box;
  }
  else {
    $box = $form_state['box'];
  }

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#required' => TRUE,
    '#default_value' => $box->label,
    '#description' => t('Name that displays in the admin interface'),
    '#weight' => -10,
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The Title of the block.'),
    '#default_value' => $box->title,
    '#weight' => -9,
  );

  // The view mode.
  if (user_access('edit box view mode')) {
    $box_info = $box->entityInfo();
    $view_modes = array_keys($box_info['view modes']);
    $view_modes = array_combine($view_modes, $view_modes);

    $form['view_mode'] = array(
      '#title' => t('View Mode'),
      '#description' => t('Edit the view mode of the Box'),
      '#default_value' => $box->view_mode,
      '#type' => 'select',
      '#required' => TRUE,
      '#options' => $view_modes,
      '#weight' => -8,
    );
  }
  else {
    $form['view_mode'] = array(
      '#type' => 'value',
      '#value' => $box->view_mode,
    );
  }

  $form['box'] = array(
    '#type' => 'value',
    '#value' => $box,
  );

  // Get the Box type form.
  $form += $box->getForm($form, $form_state);

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 200,
    '#submit' => array('boxes_form_submit'),
  );
  if (!empty($box->bid) && user_access('delete any ' . $box->type . ' boxes')) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 201,
      '#submit' => array('boxes_form_delete_submit'),
    );
  }

  $form['#validate'][] = 'boxes_form_validate';
  if (!isset($form['#submit']) && function_exists($box->type . '_boxes_form_submit')) {
    $form['#submit'][] = $box->type . '_boxes_form_submit';
  }
  $form += array('#submit' => array());

  field_attach_form('box', $box, $form, $form_state);
  return $form;
}

/**
 * Validation for box form
 */
function boxes_form_validate($form, &$form_state) {
  $box = $form_state['values']['box'];
  $box->label = $form_state['values']['label'];
  $box->title = $form_state['values']['title'];
  $box->view_mode = $form_state['values']['view_mode'];

  field_attach_form_validate('box', $box, $form, $form_state);
  $form_state['values']['box'] = $box;

  $box->validate($form_state['values'], $form_state);
}

/**
 * Submit function for box form
 */
function boxes_form_submit($form, &$form_state) {
  $box = boxes_form_submit_build_box($form, $form_state);
  $box->setValues($form_state['values']);
  $insert = $box->internalIdentifier();
  field_attach_submit('box', $box, $form, $form_state);
  $box->save();

  $watchdog_args = array('@type' => $box->typeName(), '%title' => $box->label());
  $t_args = array('@type' => $box->typeName(), '%title' => $box->label());

  if ($insert) {
    watchdog('boxes', '@type: added %title.', $watchdog_args, WATCHDOG_NOTICE, $box->viewURL());
    drupal_set_message(t('@type %title has been created.', $t_args));
  }
  else {
    watchdog('boxes', '@type: updated %title.', $watchdog_args, WATCHDOG_NOTICE, $box->viewURL());
    drupal_set_message(t('@type %title has been updated.', $t_args));
  }

  if ($box->identifier()) {
    $form_state['redirect'] = $box->viewURL();
  }
  else {
    // In the unlikely case something went wrong on save, the box will be
    // rebuilt and box form redisplayed the same way as in preview.
    drupal_set_message(t('The block could not be saved.'), 'error');
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Updates the form state's box entity by processing this submission's values.
 *
 * This is the default builder function for the box form. It is called
 * during the "Save" and "Preview" submit handlers to retrieve the entity to
 * save or preview. This function can also be called by a "Next" button of a
 * wizard to update the form state's entity with the current step's values
 * before proceeding to the next step.
 *
 * @see boxes_form()
 * @see node_form_submit_build_node()
 */
function boxes_form_submit_build_box($form, &$form_state) {

  // @todo Legacy support for modules that extend the box form with form-level
  //   submit handlers that adjust $form_state['values'] prior to those values
  //   being used to update the entity. Module authors are encouraged to instead
  //   adjust the box directly within a hook_boxes_submit() implementation. For
  //   Drupal 8, evaluate whether the pattern of triggering form-level submit
  //   handlers during button-level submit processing is worth supporting
  //   properly, and if so, add a Form API function for doing so.
  unset($form_state['submit_handlers']);
  form_execute_handlers('submit', $form, $form_state);

  $box = $form_state['box'];
  entity_form_submit_build_entity('box', $box, $form, $form_state);

  foreach (module_implements('boxes_submit') as $module) {
    $function = $module . '_boxes_submit';
    $function($box, $form, $form_state);
  }
  return $box;
}

/**
 * Button submit function: handle the 'Delete' button on the box form.
 */
function boxes_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $box = $form_state['values']['box'];
  $form_state['redirect'] = array($box->deleteURL(), array('query' => $destination));
}

/**
 * Menu callback -- ask for confirmation of box deletion
 */
function boxes_delete_confirm($form, &$form_state, $box) {
  $form['#box'] = $box;

  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $box->label())),
    $box->viewUrl(),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute box deletion
 */
function boxes_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $box = $form['#box'];
    $box->delete();
    watchdog('boxes', '@type: deleted %title.', array('@type' => $box->typeName(), '%title' => $box->label()));
    drupal_set_message(t('@type %title has been deleted.', array('@type' => $box->typeName(), '%title' => $box->label())));
  }

  $form_state['redirect'] = '<front>';
}

function boxes_filter_form($form, &$form_state) {
  $filters = boxes_get_filter();

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $type_options = array();
  foreach (boxes_get_types() as $type) {
    $type_options[$type->type] = $type->getLabel();
  }
  asort($type_options);

  $form['filters']['types'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#multiple' => TRUE,
    '#options' => $type_options,
    '#default_value' => $filters['types'],
  );

  $form['filters']['per_page'] = array(
    '#type' => 'select',
    '#title' => t('Items Per Page'),
    '#multiple' => FALSE,
    '#options' => array(20 => '20', 50 => '50', 100 => '100', 200 => '200', 500 => '500'),
    '#default_value' => $filters['per_page'],
  );

  $form['filters']['filter'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('boxes_filter_submit'),
  );
  $form['filters']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('boxes_reset_filter_submit'),
  );

  return $form;
}

/**
 * Submit function for filter
 */
function boxes_filter_submit($form, &$form_state) {
  $filters = array(
    'types' => $form_state['values']['filters']['types'],
    'per_page' => $form_state['values']['filters']['per_page'],
  );

  boxes_set_filter($filters);

  drupal_goto('admin/content/blocks');

}

/**
 * Reset the form filter options
 */
function boxes_reset_filter_submit($form, &$form_state) {
  boxes_reset_filter();

  drupal_goto('admin/content/blocks');
}

/**
 * Set the filter in the session
 */
function boxes_set_filter($filter) {
  $_SESSION['boxes-filter'] = $filter;
}

/**
 * Get the filter
 */
function boxes_get_filter() {
  // Pull any saved values from the session.
  $filters = isset($_SESSION['boxes-filter']) ? $_SESSION['boxes-filter'] : array();
  // ...fill in gaps with default values.
  return $filters + array('types' => array(), 'per_page' => 50);
}

/**
 * Reset the filter
 */
function boxes_reset_filter() {
  unset($_SESSION['boxes-filter']);
}
