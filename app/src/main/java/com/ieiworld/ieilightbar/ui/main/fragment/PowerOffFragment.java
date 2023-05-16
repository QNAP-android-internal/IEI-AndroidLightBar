package com.ieiworld.ieilightbar.ui.main.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;

import androidx.fragment.app.Fragment;

import com.ieiworld.ieilightbar.JniMethod;
import com.ieiworld.ieilightbar.R;
import com.ieiworld.ieilightbar.util.Constant;

public class PowerOffFragment extends Fragment {
    private int mFlagIdx = 0;

    public PowerOffFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_power_off, container, false);
        ButtonInit(root);
        SpinnerInit(root);
        return root;
    }

    private void SpinnerInit(View root) {
        Spinner flagSpinner = root.findViewById(R.id.sp_flag);
        ArrayAdapter<CharSequence> flagAdapter = ArrayAdapter.createFromResource(getContext(),
                R.array.flag_array, android.R.layout.simple_spinner_item);
        flagAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        flagSpinner.setAdapter(flagAdapter);
        flagSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int pos, long id) {
                mFlagIdx = pos;
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
            }
        });
    }

    private void ButtonInit(View root) {
        Button saveButton = root.findViewById(R.id.btn_save);
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                JniMethod.getInstance().setLightBarPowerLedPoweroffState(Constant.LED_FLAGS[mFlagIdx]);
            }
        });
    }
}