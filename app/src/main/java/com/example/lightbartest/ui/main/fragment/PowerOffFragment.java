package com.example.lightbartest.ui.main.fragment;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;

import androidx.fragment.app.Fragment;

import com.example.lightbartest.JniMethod;
import com.example.lightbartest.util.Constant;
import com.example.lightbartest.R;

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
                String saveResult = JniMethod.getInstance().getLightBarPowerLedStatus("poweroff");
                onCreateDialog(saveResult.equals(Constant.LED_FLAGS[mFlagIdx])).show();
            }
        });
    }

    private Dialog onCreateDialog(boolean result) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        if (result) {
            builder.setTitle("Save Success");
            builder.setMessage("Please reboot and configuration will take effect");
        } else {
            builder.setTitle("Save Fail");
            builder.setMessage("Please check SELinux setting");
        }
        builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int id) {
                dialogInterface.cancel();
            }
        });

        return builder.create();
    }
}