<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the defaults.
 */
class BoxMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['label'] = array(
      'label' => t('Label'),
      'description' => t('The box label'),
      'getter callback' => 'entity_property_getter_method',
      'schema field' => 'label',
    );

    $properties['title'] = array(
      'label' => t('Title'),
      'description' => t('The box title'),
      'getter callback' => 'entity_property_getter_method',
      'schema field' => 'title',
    );

    $properties['view_mode'] = array(
      'label' => t('View Mode'),
      'description' => t('View mode of the box'),
      'getter callback' => 'entity_property_getter_method',
      'schema field' => 'view_mode',
      'required' => TRUE,
    );

    $properties['delta'] = array(
      'getter callback' => 'entity_property_getter_method',
      'description' => t('The box delta.'),
      'label' => t('Block Delta'),
      'required' => TRUE,
      'schema field' => 'delta',
    );

    $properties['type'] = array(
      'type' => 'box_type',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer boxes',
      'required' => TRUE,
      'description' => t('The box type.'),
    ) + $properties['type'];

    return $info;
  }
}