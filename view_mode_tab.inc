<?php

/**
 * Loads all the view modes for this node and then outputs them.
 */
function _view_mode_tab_load($entity_type, $entity) {
  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
  $output = '';
  $settings = variable_get('view_mode_tab_settings__' . $entity_type . '__' . $bundle, array());

  $entity_info = entity_get_info();

  if (!empty($entity_info[$entity_type]['view modes'])) {
    $view_modes = array_keys($entity_info[$entity_type]]['view modes']);

    $header = array();
    $rendered_entity = array();
    $uri_info = entity_uri($entity_type, $entity);
    foreach ($view_modes as $view_mode) {
      if (!isset($settings[$view_mode]) || $settings[$view_mode] !== 0) {
        $id = drupal_html_id($view_mode);
        $header[] = l($view_mode, $uri_info['path'] . '/view_modes', array('fragment' => $id));
        $rendered_entity[$view_mode] = array(
          'view_mode' => entity_view($entity_type, $entity, $view_mode),
          'header_id' => $id,
        );
      }
    }

    $output .= theme('item_list', array('items' => $header));
    $output .= theme('view_mode_tab_display', array('view_modes' => $rendered_entity, $entity_type => $node));
  }
  return $output;
}
