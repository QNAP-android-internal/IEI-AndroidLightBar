package com.example.lightbartest.ui.main.fragment;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.RadioGroup;
import android.widget.Spinner;

import androidx.fragment.app.Fragment;

import com.example.lightbartest.LedModeService;
import com.example.lightbartest.util.Constant;
import com.example.lightbartest.R;

public class UserFeatureFragment extends Fragment {
    private int mColorIdx = 0;

    public UserFeatureFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_user_feature, container, false);
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
        Button btnRun = root.findViewById(R.id.btn_run);
        Button btnStop = root.findViewById(R.id.btn_stop);
        RadioGroup modeRadioGp = root.findViewById(R.id.rg_mode);
        btnRun.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final Intent intent = new Intent();
                final Bundle b = new Bundle();
                b.putBoolean(Constant.IS_LED_SERVICE_START, true);
                if (modeRadioGp.getCheckedRadioButtonId() == R.id.rb_breath) {
                    b.putInt(Constant.LED_MODE, Constant.LED_MODE_BREATH);
                } else {
                    b.putInt(Constant.LED_MODE, Constant.LED_MODE_WAVE);
                }
                b.putString(Constant.LED_COLOR, Constant.LED_COLORS[mColorIdx]);
                intent.putExtras(b);
                intent.setClass(getContext(), LedModeService.class);
                intent.setPackage(getContext().getPackageName());
                getContext().startService(intent);
            }
        });

        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final Intent intent = new Intent();
                final Bundle b = new Bundle();
                b.putBoolean(Constant.IS_LED_SERVICE_START, false);
                intent.setPackage(getContext().getPackageName());
                intent.setClass(getContext(), LedModeService.class);
                getContext().stopService(intent);
            }
        });
    }
}