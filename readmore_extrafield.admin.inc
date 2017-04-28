<?php

function readmore_extrafield_admin_form($form, &$form_state)
{
    $settings = variable_get('readmore_extrafield_variables', array());


    $entities = array();
    foreach (entity_get_info() as $type => $info) {
        $full_info = entity_get_info($type);
        if (isset($full_info['fieldable'], $full_info['bundles']) && $full_info['fieldable']) {
            $entities[$type] = array_keys($full_info['bundles']);
        }
    }

    $form['readmore_extrafield_variables'] = array(
        '#type' => 'vertical_tabs',
        '#tree' => true,
    );

    foreach ($entities as $type => $bundles) {

        foreach ($bundles as $bundle) {

            $key = $type.'--'.$bundle;
            $form['readmore_extrafield_variables'][$key] = array(
                '#type' => 'fieldset',
                '#title' => $type.'--'.$bundle,
            );

            $form['readmore_extrafield_variables'][$key][] = array(
                '#markup' => '<h3>'.t('Entity : @type--@bundle', array('@type' => $type, '@bundle' => $bundle)).'</h3>',
            );

            $form['readmore_extrafield_variables'][$key]['enable_extra_field'] = array(
                '#type' => 'checkbox',
                '#title' => t('Enable <em>Read more</em> extra field'),
                '#default_value' => isset($settings[$key]['enable_extra_field']) ? $settings[$key]['enable_extra_field'] : 0,
            );

            $form['readmore_extrafield_variables'][$key]['hide_default_link'] = array(
                '#type' => 'checkbox',
                '#title' => t('Hide default <em>Read more</em> link'),
                '#default_value' => isset($settings[$key]['hide_default_link']) ? $settings[$key]['hide_default_link'] : 0,
            );

            $form['readmore_extrafield_variables'][$key]['settings'] = array(
                '#type' => 'fieldset',
                '#title' => t('Settings'),
                '#states' => array(
                    'invisible' => array(
                        'input[name="readmore_extrafield_variables['.$key.'][enable_extra_field]"]' => array('checked' => false),
                    ),
                ),
            );

            $form['readmore_extrafield_variables'][$key]['settings']['text'] = array(
                '#type' => 'textfield',
                '#title' => t('Link text'),
                '#default_value' => isset($settings[$key]['settings']['text']) ? $settings[$key]['settings']['text'] : READMORE_EXTRAFIELD_DEFAULT_TEXT,
            );

            $form['readmore_extrafield_variables'][$key]['settings']['class'] = array(
                '#type' => 'textfield',
                '#title' => t('Link CSS class'),
                '#description' => t('Multiple classes separated by space'),
                '#default_value' => isset($settings[$key]['settings']['class']) ? $settings[$key]['settings']['class'] : '',
            );
        }
    }

    $form['#submit'][] = 'readmore_extrafield_admin_form_submit';

    return system_settings_form($form);
}

function readmore_extrafield_admin_form_submit($form, &$form_state)
{
    // flush the field module cache
    $cache_tables = module_invoke('field', 'flush_caches');
    foreach ($cache_tables as $table) {
        cache_clear_all('*', $table, true);
    }
    drupal_set_message(t('Fields cache flushed'), 'status', false);
}
