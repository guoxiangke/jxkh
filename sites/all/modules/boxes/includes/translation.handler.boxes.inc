<?php

/**
 * @file
 * Box translation handler for the translation module.
 */


/**
 * Box translation handler.
 *
 * Overrides default behaviours for Box properties.
 */
class EntityTranslationBoxHandler extends EntityTranslationDefaultHandler {

  public function __construct($entity_type, $entity_info, $entity, $entity_id) {
    parent::__construct('box', $entity_info, $entity, $entity_id);
  }

  public function getAccess($op) {
    return boxes_access($op, $this->entity);
  }

  protected function getEntityId() {
    return $this->entity->delta;
  }
}
