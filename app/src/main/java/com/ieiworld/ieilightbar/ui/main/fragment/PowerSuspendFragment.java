package com.ieiworld.ieilightbar.ui.main.fragment;

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

import com.ieiworld.ieilightbar.JniMethod;
import com.ieiworld.ieilightbar.R;
import com.ieiworld.ieilightbar.util.Constant;


public class PowerSuspendFragment extends Fragment {
    private int mColorIdx = 0;

    public PowerSuspendFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_power_suspend, container, false);
        ButtonInit(root);
        SpinnerInit(root);
        return root;
    }

    private void SpinnerInit(View root) {
        Spinner colorSpinner = root.findViewById(R.id.sp_color);
        ArrayAdapter<CharSequence> colorAdapter = ArrayAdapter.createFromResource(getContext(),
                R.array.color_array, android.R.layout.simple_spinner_item);
        colorAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        colorSpinner.setAdapter(colorAdapter);
        colorSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int pos, long id) {
                mColorIdx = pos;
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
                JniMethod.getInstance().setLightBarPowerLedSuspendColor(Constant.LED_COLORS[mColorIdx]);
                String saveResult = JniMethod.getInstance().getLightBarPowerLedStatus("suspend");
                onCreateDialog(saveResult.equals(Constant.LED_COLORS[mColorIdx])).show();
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