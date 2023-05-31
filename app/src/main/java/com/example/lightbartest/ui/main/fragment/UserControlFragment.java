package com.example.lightbartest.ui.main.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.SeekBar;
import android.widget.Spinner;

import androidx.fragment.app.Fragment;

import com.example.lightbartest.JniMethod;
import com.example.lightbartest.R;

public class UserControlFragment extends Fragment {
    private int mRedBrightness = 0, mGreenBrightness = 0, mBlueBrightness = 0;
    private int mBarNum = 1, mLedNum = 1;
    private SeekBar mRedSeekBar, mGreenSeekBar, mBlueSeekBar;
    private Spinner mBarNumSpinner, mLedNumSpinner;

    public UserControlFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_user_control, container, false);
        SpinnerInit(root);
        SeekBarInit(root);
        root.findViewById(R.id.btn_clear).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                resetLedStatus();
            }
        });

        return root;
    }

    private void SpinnerInit(View root) {
        mBarNumSpinner = root.findViewById(R.id.sp_bar_num);
        ArrayAdapter<CharSequence> barNumAdapter = ArrayAdapter.createFromResource(getContext(),
                R.array.bar_num_array, android.R.layout.simple_spinner_item);
        barNumAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mBarNumSpinner.setAdapter(barNumAdapter);
        mBarNumSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int pos, long id) {
                mBarNum = pos + 1;
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
            }
        });

        mLedNumSpinner = root.findViewById(R.id.sp_led_num);
        ArrayAdapter<CharSequence> ledNumAdapter = ArrayAdapter.createFromResource(getContext(),
                R.array.led_num_array, android.R.layout.simple_spinner_item);
        ledNumAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mLedNumSpinner.setAdapter(ledNumAdapter);
        mLedNumSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int pos, long id) {
                mLedNum = pos + 1;
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
            }
        });
    }

    private void SeekBarInit(View root) {
        mRedSeekBar = root.findViewById(R.id.sb_red);
        mGreenSeekBar = root.findViewById(R.id.sb_green);
        mBlueSeekBar = root.findViewById(R.id.sb_blue);
        mRedSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                mRedBrightness = progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JniMethod.getInstance().setLightBarUserLED(mBarNum, mLedNum, mRedBrightness, mGreenBrightness, mBlueBrightness);
            }
        });

        mGreenSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                mGreenBrightness = progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JniMethod.getInstance().setLightBarUserLED(mBarNum, mLedNum, mRedBrightness, mGreenBrightness, mBlueBrightness);
            }
        });

        mBlueSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                mBlueBrightness = progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JniMethod.getInstance().setLightBarUserLED(mBarNum, mLedNum, mRedBrightness, mGreenBrightness, mBlueBrightness);
            }
        });
    }

    private void resetLedStatus() {
        JniMethod.getInstance().clearLightBarLED();
        mBarNumSpinner.setSelection(0);
        mLedNumSpinner.setSelection(0);
        mRedSeekBar.setProgress(0);
        mGreenSeekBar.setProgress(0);
        mBlueSeekBar.setProgress(0);
    }
}

